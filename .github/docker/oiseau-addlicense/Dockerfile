# Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
#
# This file is part of oiseau (https://github.com/tiagovla/oiseau)
#
# SPDX-License-Identifier: GPL-3.0-or-later

# Use Go image to build the binary
FROM golang:1.16 AS build

WORKDIR /build

# Clone the addlicense repository
RUN git clone https://github.com/google/addlicense.git

WORKDIR /build/addlicense

# Download dependencies
RUN go mod download

# Build the binary for Linux with no CGO
RUN CGO_ENABLED=0 GOOS=linux go build -o /app/addlicense

# Minimal final image
FROM scratch

# Source to be scanned should be mounted to /src
WORKDIR /src

# Copy only the built binary from builder
COPY --from=build /app/addlicense /app/addlicense

ENTRYPOINT ["/app/addlicense"]
