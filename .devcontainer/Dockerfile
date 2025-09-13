FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04 as base

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="none"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

RUN yes | unminimize && \
    apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    zsh \
    man-db \
    manpages-dev \
    manpages-posix-dev \
    cppreference-doc-en-html \
    && mandb \
    && rm -rf /var/lib/apt/lists/*

FROM base as development

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    vim \
    valgrind \
    tree \
    file \
    strace \
    ltrace \
    htop \
    nasm \
    xdd \
    && rm -rf /var/lib/apt/lists/*

RUN usermod --shell /bin/zsh vscode
RUN mkdir -p /workspaces && chown -R vscode:vscode /workspaces
RUN echo 'alias cdh="cd /workspaces"' >> /home/vscode/.bashrc

COPY --chown=vscode:vscode ./.gdbinit /home/vscode/.gdbinit