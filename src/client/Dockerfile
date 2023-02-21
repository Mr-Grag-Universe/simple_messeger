FROM cpp-build-base:0.1.0 AS build

# WORKDIR .

COPY . .
COPY . ../../cmake-build-debug-mingw/src/client/client_lib/src/libMyClientLib.a
# CMakeLists.txt main.cpp ./client_lib/

RUN mkdir build
# WORKDIR build

# RUN cmake .. && make
RUN g++ main.cpp -lMyClientLib.a

FROM ubuntu:bionic

RUN ls -a
# WORKDIR /opt/hello-world

# COPY --from=build /src/simple_messeger ./

CMD ["./MyClient"]