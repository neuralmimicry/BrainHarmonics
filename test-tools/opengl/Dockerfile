FROM openglfw
MAINTAINER Matt McCormick <matt.mccormick@kitware.com>

add * /home/user/source/
add ./cmake_script /home/user/cmake_script 
run bash /home/user/cmake_script

# OCI metadata (final stage) so GHCR links the package to its source repository.
LABEL org.opencontainers.image.source="https://github.com/neuralmimicry/BrainHarmonics" \
      org.opencontainers.image.url="https://github.com/neuralmimicry/BrainHarmonics" \
      org.opencontainers.image.description="BrainHarmonics OpenGL test-tools image" \
      org.opencontainers.image.vendor="NeuralMimicry" \
      org.opencontainers.image.licenses="GPL-3.0-only"
