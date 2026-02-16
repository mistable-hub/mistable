#!/usr/bin/env python3
import os
import re
import subprocess
import sys


def load_lines(path, visited=None):
    if visited is None:
        visited = set()
    if path in visited:
        return []
    visited.add(path)
    lines = []
    base_dir = os.path.dirname(path)
    with open(path, 'r', encoding='utf-8') as f:
        for raw in f:
            line = raw.rstrip('\n')
            if line.startswith('include '):
                inc = line.split(' ', 1)[1].strip()
                inc_path = os.path.join(base_dir, inc)
                if os.path.exists(inc_path):
                    lines.extend(load_lines(inc_path, visited))
                continue
            lines.append(line)
    return lines


def parse_build_ninja(path):
    rules = {}
    builds = []
    vars_map = {}
    current_rule = None
    lines = load_lines(path)
    i = 0
    while i < len(lines):
        line = lines[i]
        if not line or line.startswith('#'):
            i += 1
            continue
        if line.startswith('rule '):
            current_rule = line.split(' ', 1)[1].strip()
            rules[current_rule] = {}
            i += 1
            continue
        if current_rule and line.startswith('  command = '):
            rules[current_rule]['command'] = line[len('  command = '):]
            i += 1
            continue
        if ' = ' in line and not line.startswith('build ') and not line.startswith('rule ') and not line.startswith('  '):
            key, val = line.split(' = ', 1)
            vars_map[key.strip()] = val.strip()
            i += 1
            continue
        if line.startswith('build '):
            left, right = line.split(':', 1)
            outputs = left.split()[1:]
            parts = right.strip().split()
            if not parts:
                i += 1
                continue
            rule = parts[0]
            inputs = []
            for tok in parts[1:]:
                if tok in ('|', '||'):
                    break
                inputs.append(tok)
            build_vars = {}
            j = i + 1
            while j < len(lines) and lines[j].startswith('  '):
                if ' = ' in lines[j]:
                    key, val = lines[j].split(' = ', 1)
                    build_vars[key.strip()] = val.strip()
                j += 1
            builds.append((outputs, rule, inputs, build_vars))
            i = j
            continue
        i += 1
    return rules, builds, vars_map


def expand_command(cmd, outputs, inputs, vars_map, build_vars):
    merged = dict(vars_map)
    merged.update(build_vars)
    cmd = cmd.replace('$in_newline', ' '.join(inputs))
    cmd = cmd.replace('$out_newline', ' '.join(outputs))
    cmd = cmd.replace('$in', ' '.join(inputs))
    cmd = cmd.replace('$out', ' '.join(outputs))
    cmd = re.sub(r'\$\{([A-Za-z0-9_]+)\}', lambda m: merged.get(m.group(1), ''), cmd)
    cmd = re.sub(r'\$([A-Za-z0-9_]+)', lambda m: merged.get(m.group(1), ''), cmd)
    return cmd


def main():
    args = sys.argv[1:]
    if '--version' in args:
        print('1.11.0-stub')
        return 0

    if '-C' in args:
        idx = args.index('-C')
        if idx + 1 < len(args):
            os.chdir(args[idx + 1])
            del args[idx:idx + 2]

    cwd = os.getcwd()
    if 'CMakeScratch' in cwd or 'TryCompile' in cwd:
        return 0

    for arg in args:
        if arg.startswith('cmTC_'):
            return 0

    if '-t' in args:
        return 0

    build_ninja = os.path.join(os.getcwd(), 'build.ninja')
    if not os.path.exists(build_ninja):
        print('build.ninja not found', file=sys.stderr)
        return 1

    rules, builds, vars_map = parse_build_ninja(build_ninja)
    if not rules or not builds:
        return 0

    for outputs, rule, inputs, build_vars in builds:
        if rule not in rules or 'command' not in rules[rule]:
            continue
        cmd = expand_command(rules[rule]['command'], outputs, inputs, vars_map, build_vars)
        cmd = re.sub(r'\|\|\s*cmake_object_order_depends_target_[A-Za-z0-9_]+', '', cmd)
        if not cmd.strip():
            continue
        print(cmd)
        subprocess.check_call(cmd, shell=True)

    return 0


if __name__ == '__main__':
    sys.exit(main())
