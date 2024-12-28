
# Amazon Locker System Requirements

## 1. System Overview
An automated locker system that enables secure package delivery and pickup services.

## 2. Functional Requirements

### 2.1 Package Delivery
- System must support placing packages in available lockers
- Support multiple locker sizes (XS, S, M, L, XL, XXL)
- Generate unique access codes for package pickup
- Validate package dimensions against locker capacity
- Maximum package size: 20,000 cubic centimeters

### 2.2 Package Pickup
- Verify access codes for package retrieval
- Access codes expire after 3 days
- Display remaining pickup time
- Support package removal from lockers
- Validate pickup authorization

### 2.3 Locker Management
- Track locker availability status
- Support multiple locker locations
- Display locker size distribution
- Monitor package pickup deadlines
- Support package returns

## 3. Technical Requirements

### 3.1 System Architecture
- C++ implementation
- Object-oriented design
- Console-based user interface
- Real-time status updates

### 3.2 Data Management
- In-memory storage for demonstration
- Support for package, locker, and location data
- Unique identifiers for orders, packages, and lockers

### 3.3 Security
- OTP-based access control
- Time-limited access codes
- Secure package storage

## 4. Locker Specifications

### 4.1 Locker Sizes
- Extra Small: Up to 500 cubic cm
- Small: 501-1000 cubic cm
- Medium: 1001-2500 cubic cm
- Large: 2501-5000 cubic cm
- Extra Large: 5001-10000 cubic cm
- Double Extra Large: 10001-20000 cubic cm

### 4.2 Location Configuration
- Multiple lockers per location
- Varied size distribution
- Geographic location tracking

## 5. User Interface Requirements
- Clear menu-driven interface
- Package size guide display
- Status notifications
- Error messaging
- Locker availability display

## 6. Error Handling
- Invalid access code management
- Full locker handling
- Package size validation
- Expired code handling
- System error recovery
