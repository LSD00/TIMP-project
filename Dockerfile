# Сборка
FROM ubuntu:22.04 AS builder
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    libqt6sql6-psql \
    libgl1-mesa-dev \
    libpq-dev \
    libssl-dev

WORKDIR /app
COPY . .
RUN mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make -j$(nproc)

# Исполнение
FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    qt6-base-dev \
    libqt6sql6-psql \
    libpq5 \
    libssl-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/build/TcpServer /app/TcpServer
COPY --from=builder /app/build/libCalcLib.so /usr/lib/

EXPOSE 8080
CMD ["./TcpServer"]