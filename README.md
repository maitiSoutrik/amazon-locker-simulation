# Clone the repository
git clone https://github.com/maitiSoutrik/amazon-locker.git
cd amazon-locker

# Create build directory
mkdir -p build && cd build

# Configure and build
cmake ..
make

# Run tests
ctest --output-on-failure