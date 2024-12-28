
# Amazon Locker System

A C++ implementation of an automated locker system that enables secure package delivery and pickup services.

## Features

- Package delivery and pickup management
- Multiple locker sizes (XS, S, M, L, XL, XXL)
- Unique access code generation
- Package dimension validation
- Location-based locker management
- Console-based user interface

## Building and Running

### Prerequisites

- C++ compiler supporting C++17
- CMake 3.10 or higher

### Build Instructions

1. Fork/Clone this project on Replit
2. The project will automatically build using CMake

### Running the Application

1. Click the "Run" button in Replit
2. Follow the console menu prompts to:
   - Deliver packages
   - Pick up packages
   - View locker status
   - Generate access codes
   - Manage package returns

## Testing

The project includes unit tests using Google Test framework. To run the tests:

1. Build the project
2. Execute the test binary:
   ```
   ./bins/amazon_locker_test
   ```

## Project Structure

- `include/` - Header files
- `src/` - Source files
- `tests/` - Unit tests
- `app/` - Application specific code

## Documentation

Documentation is generated using Doxygen. To view the documentation, run:
```
doxygen Doxyfile
python3 -m http.server 8080 --directory doc/html --bind 0.0.0.0
```
Then open the webview in Replit to access the documentation.
