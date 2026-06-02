FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j$(nproc)

RUN cd build && ctest --output-on-failure

FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/proxy_server /usr/local/bin/proxy_server
COPY --from=builder /app/build/tests/unit_tests /usr/local/bin/unit_tests
COPY --from=builder /app/build/tests/scenario_tests /usr/local/bin/scenario_tests
COPY --from=builder /app/config.txt /app/config.txt

EXPOSE 8080

ENTRYPOINT ["/usr/local/bin/proxy_server"]
CMD ["/app/config.txt"]
