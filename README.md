# mistable

Phase 0 minimal spine. This builds and runs a Verilator simulation that emits a single frame image.

## Run on Host

./scripts/test.sh

## Run via Docker

docker build -t mistable-dev -f container/Dockerfile .
docker run --rm -it -v "$PWD:/work" -w /work mistable-dev ./scripts/test.sh

## Trusted interactive shell

./dev

Inside the container:

./scripts/sanity.sh

## Output Artifact

The simulation produces build/frame.ppm, a binary PPM (P6) image containing a deterministic test pattern.
