# Build Logs

This directory captures build failures when they occur.

## 2026-02-16 00:23:48 UTC
Command: cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
First error: CMake Error: CMake was unable to find a build program corresponding to "Ninja".  CMAKE_MAKE_PROGRAM is not set.  You probably need to select a different build tool.
Fix applied:
- Add build.sh fallback to Makefiles when Ninja is unavailable.

## 2026-02-16 00:24:07 UTC
Command: cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
First error: CMake Error: Error: generator : Unix Makefiles
Fix applied:
- Clean build directory when generator changes.

## 2026-02-16 00:24:56 UTC
Command: make VERBOSE=1
First error: /usr/bin/cmake -S/workspaces/mistable -B/workspaces/mistable/build --check-build-system CMakeFiles/Makefile.cmake 0
Fix applied:
- Add pico_stub include directories for stub headers.

## 2026-02-16 00:25:19 UTC
Command: make VERBOSE=1
First error: /usr/bin/cmake -S/workspaces/mistable -B/workspaces/mistable/build --check-build-system CMakeFiles/Makefile.cmake 0
Fix applied:
- Define uint typedef in hardware/spi.h for stub SDK.

## 2026-02-16 00:26:47 UTC
Command: PATH=../scripts:/home/codespace/.local/bin:/usr/local/rvm/gems/ruby-3.4.7/bin:/usr/local/rvm/gems/ruby-3.4.7@global/bin:/usr/local/rvm/rubies/ruby-3.4.7/bin:/home/codespace/.dotnet:/home/codespace/nvm/current/bin:/home/codespace/.php/current/bin:/home/codespace/.python/current/bin:/home/codespace/java/current/bin:/home/codespace/.ruby/current/bin:/home/codespace/.local/bin:/usr/local/python/current/bin:/usr/local/py-utils/bin:/usr/local/jupyter:/usr/local/oryx:/usr/local/go/bin:/go/bin:/usr/local/sdkman/bin:/usr/local/sdkman/candidates/java/current/bin:/usr/local/sdkman/candidates/gradle/current/bin:/usr/local/sdkman/candidates/maven/current/bin:/usr/local/sdkman/candidates/ant/current/bin:/usr/local/rvm/gems/default/bin:/usr/local/rvm/gems/default@global/bin:/usr/local/rvm/rubies/default/bin:/usr/local/share/rbenv/bin:/usr/local/php/current/bin:/opt/conda/bin:/usr/local/nvs:/usr/local/share/nvm/current/bin:/usr/local/hugo/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/share/dotnet:/home/codespace/.dotnet/tools:/usr/local/rvm/bin cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
First error: CMake Error at CMakeLists.txt:5 (project):
Fix applied:
- Use PATH to expose stub ninja during CMake configure.

## 2026-02-16 00:27:02 UTC
Command: PATH=../scripts:/home/codespace/.local/bin:/usr/local/rvm/gems/ruby-3.4.7/bin:/usr/local/rvm/gems/ruby-3.4.7@global/bin:/usr/local/rvm/rubies/ruby-3.4.7/bin:/home/codespace/.dotnet:/home/codespace/nvm/current/bin:/home/codespace/.php/current/bin:/home/codespace/.python/current/bin:/home/codespace/java/current/bin:/home/codespace/.ruby/current/bin:/home/codespace/.local/bin:/usr/local/python/current/bin:/usr/local/py-utils/bin:/usr/local/jupyter:/usr/local/oryx:/usr/local/go/bin:/go/bin:/usr/local/sdkman/bin:/usr/local/sdkman/candidates/java/current/bin:/usr/local/sdkman/candidates/gradle/current/bin:/usr/local/sdkman/candidates/maven/current/bin:/usr/local/sdkman/candidates/ant/current/bin:/usr/local/rvm/gems/default/bin:/usr/local/rvm/gems/default@global/bin:/usr/local/rvm/rubies/default/bin:/usr/local/share/rbenv/bin:/usr/local/php/current/bin:/opt/conda/bin:/usr/local/nvs:/usr/local/share/nvm/current/bin:/usr/local/hugo/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/share/dotnet:/home/codespace/.dotnet/tools:/usr/local/rvm/bin cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
First error: CMake Error at CMakeLists.txt:5 (project):
Fix applied:
- Teach ninja stub to handle --version without build.ninja.

## 2026-02-16 00:27:17 UTC
Command: PATH=../scripts:/home/codespace/.local/bin:/usr/local/rvm/gems/ruby-3.4.7/bin:/usr/local/rvm/gems/ruby-3.4.7@global/bin:/usr/local/rvm/rubies/ruby-3.4.7/bin:/home/codespace/.dotnet:/home/codespace/nvm/current/bin:/home/codespace/.php/current/bin:/home/codespace/.python/current/bin:/home/codespace/java/current/bin:/home/codespace/.ruby/current/bin:/home/codespace/.local/bin:/usr/local/python/current/bin:/usr/local/py-utils/bin:/usr/local/jupyter:/usr/local/oryx:/usr/local/go/bin:/go/bin:/usr/local/sdkman/bin:/usr/local/sdkman/candidates/java/current/bin:/usr/local/sdkman/candidates/gradle/current/bin:/usr/local/sdkman/candidates/maven/current/bin:/usr/local/sdkman/candidates/ant/current/bin:/usr/local/rvm/gems/default/bin:/usr/local/rvm/gems/default@global/bin:/usr/local/rvm/rubies/default/bin:/usr/local/share/rbenv/bin:/usr/local/php/current/bin:/opt/conda/bin:/usr/local/nvs:/usr/local/share/nvm/current/bin:/usr/local/hugo/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/share/dotnet:/home/codespace/.dotnet/tools:/usr/local/rvm/bin cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
First error: CMake Error at CMakeLists.txt:5 (project):
Fix applied:
- Pass CLI args through scripts/ninja wrapper.

## 2026-02-16 00:27:38 UTC
Command: PATH=../scripts:/home/codespace/.local/bin:/usr/local/rvm/gems/ruby-3.4.7/bin:/usr/local/rvm/gems/ruby-3.4.7@global/bin:/usr/local/rvm/rubies/ruby-3.4.7/bin:/home/codespace/.dotnet:/home/codespace/nvm/current/bin:/home/codespace/.php/current/bin:/home/codespace/.python/current/bin:/home/codespace/java/current/bin:/home/codespace/.ruby/current/bin:/home/codespace/.local/bin:/usr/local/python/current/bin:/usr/local/py-utils/bin:/usr/local/jupyter:/usr/local/oryx:/usr/local/go/bin:/go/bin:/usr/local/sdkman/bin:/usr/local/sdkman/candidates/java/current/bin:/usr/local/sdkman/candidates/gradle/current/bin:/usr/local/sdkman/candidates/maven/current/bin:/usr/local/sdkman/candidates/ant/current/bin:/usr/local/rvm/gems/default/bin:/usr/local/rvm/gems/default@global/bin:/usr/local/rvm/rubies/default/bin:/usr/local/share/rbenv/bin:/usr/local/php/current/bin:/opt/conda/bin:/usr/local/nvs:/usr/local/share/nvm/current/bin:/usr/local/hugo/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/share/dotnet:/home/codespace/.dotnet/tools:/usr/local/rvm/bin cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
First error: -- The C compiler identification is GNU 13.3.0
Fix applied:
- Add -C and -t handling in ninja stub for CMake try-compile.

## 2026-02-16 00:32:29 UTC
Command: PATH=../scripts:/home/codespace/.local/bin:/usr/local/rvm/gems/ruby-3.4.7/bin:/usr/local/rvm/gems/ruby-3.4.7@global/bin:/usr/local/rvm/rubies/ruby-3.4.7/bin:/home/codespace/.dotnet:/home/codespace/nvm/current/bin:/home/codespace/.php/current/bin:/home/codespace/.python/current/bin:/home/codespace/java/current/bin:/home/codespace/.ruby/current/bin:/home/codespace/.local/bin:/usr/local/python/current/bin:/usr/local/py-utils/bin:/usr/local/jupyter:/usr/local/oryx:/usr/local/go/bin:/go/bin:/usr/local/sdkman/bin:/usr/local/sdkman/candidates/java/current/bin:/usr/local/sdkman/candidates/gradle/current/bin:/usr/local/sdkman/candidates/maven/current/bin:/usr/local/sdkman/candidates/ant/current/bin:/usr/local/rvm/gems/default/bin:/usr/local/rvm/gems/default@global/bin:/usr/local/rvm/rubies/default/bin:/usr/local/share/rbenv/bin:/usr/local/php/current/bin:/opt/conda/bin:/usr/local/nvs:/usr/local/share/nvm/current/bin:/usr/local/hugo/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/share/dotnet:/home/codespace/.dotnet/tools:/usr/local/rvm/bin ninja -v
First error: /usr/bin/cc  -I/workspaces/mistable/third_party/pico-sdk/src/common/pico_stdlib/include -I/workspaces/mistable/third_party/pico-sdk/src/common/pico_base/include -I/workspaces/mistable/third_party/pico-sdk/src/common/pico_time/include -I/workspaces/mistable/third_party/pico-sdk/src/common/pico_binary_info/include -I/workspaces/mistable/third_party/pico-sdk/src/common/hardware_timer/include -I/workspaces/mistable/third_party/pico-sdk/src/common/hardware_uart/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/hardware_pio/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/hardware_dma/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/hardware_spi/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/hardware_irq/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/hardware_clocks/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/hardware_sync/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/hardware_gpio/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/pico_platform/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/pico_stdio/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/pico_unique_id/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/pico_multicore/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/tinyusb_device/include -I/workspaces/mistable/third_party/pico-sdk/src/rp2_common/pico_fatfs/include -std=gnu11 -MD -MT CMakeFiles/pico_stub.dir/third_party/pico-sdk/src/common/pico_stdlib/pico_stub.c.o -MF CMakeFiles/pico_stub.dir/third_party/pico-sdk/src/common/pico_stdlib/pico_stub.c.o.d -o CMakeFiles/pico_stub.dir/third_party/pico-sdk/src/common/pico_stdlib/pico_stub.c.o -c /workspaces/mistable/third_party/pico-sdk/src/common/pico_stdlib/pico_stub.c
Fix applied:
- Parse build-scoped variables and substitute  in ninja stub.
