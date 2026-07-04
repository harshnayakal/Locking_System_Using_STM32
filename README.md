Here's a professional **GitHub project description** for your repository.

---

# 🔐 Two-Factor Authentication (2FA) Locker System using STM32F103C8T6

## 📌 Overview

The **Two-Factor Authentication (2FA) Locker System** is an embedded security project developed using the **STM32F103C8T6 (Blue Pill)** microcontroller. The system enhances traditional password-based security by implementing a second authentication layer through a dynamically generated One-Time Password (OTP).

A user must first enter the correct password using a **4×4 matrix keypad**. After successful password verification, a random 4-digit OTP is generated and displayed on a **16×2 LCD**. Access is granted only when the correct OTP is entered. If an incorrect password is entered three consecutive times, the system enters a **100-second security lockout**, preventing unauthorized access.

The project is developed entirely using **register-level programming** in **Embedded C** on **Keil uVision**, without relying on the STM32 HAL or Standard Peripheral Library.

---

# ✨ Features

* 🔐 Two-Factor Authentication (Password + OTP)
* 🔢 4-digit password verification
* 🎲 Random 4-digit OTP generation
* ⌨️ 4×4 Matrix Keypad interface
* 📺 16×2 LCD user interface
* 🚨 Security lock after 3 incorrect password attempts
* ⏳ 100-second countdown lockout
* 🔔 Buzzer alerts for authentication status
* 💡 LED indication for lock/unlock status
* ⚡ Register-level STM32 programming
* 🧩 Modular driver-based architecture

---

# 🛠 Hardware Used

* STM32F103C8T6 (Blue Pill)
* 16×2 LCD (8-bit Mode)
* 4×4 Matrix Keypad
* Active Buzzer
* 4 LEDs
* Push Button (Start Switch)
* 5V Power Supply
* Jumper Wires

---

# 📌 Pin Configuration

| Component      | STM32 Pin |
| -------------- | --------- |
| LCD RS         | PB0       |
| LCD EN         | PB1       |
| LCD D0–D7      | PB8–PB15  |
| Keypad Rows    | PA0–PA3   |
| Keypad Columns | PA4–PA7   |
| Buzzer         | PA8       |
| LED1           | PA12      |
| LED2           | PA13      |
| LED3           | PA14      |
| LED4           | PA15      |
| Start Switch   | PB6       |

---

# 💻 Software Used

* Keil uVision 5
* STM32F10x CMSIS Device Library
* Embedded C
* Register-Level Programming

---

# 📂 Project Structure

```text
Project/
│── main.c
│── delay.c
│── delay.h
│── lcd.c
│── lcd.h
│── keypad.c
│── keypad.h
│── led.c
│── led.h
│── buzzer.c
│── buzzer.h
│── otp.c
│── otp.h
│── startup_stm32f10x_md.s
│── system_stm32f10x.c
│── system_stm32f10x.h
```

---

# ⚙️ Working Principle

1. The system waits for the **Start Switch** to be pressed.
2. The user enters a **4-digit password** using the keypad.
3. If the password is incorrect, the attempt counter increases.
4. After three incorrect attempts, the system locks for **100 seconds**.
5. If the password is correct, a **random 4-digit OTP** is generated.
6. The user enters the OTP using the keypad.
7. If the OTP matches, the locker unlocks:

   * LEDs perform an unlock animation.
   * Buzzer gives a success indication.
8. After a predefined delay, the locker locks again.

---

# 📸 Demonstration

* Password Authentication
* OTP Generation
* OTP Verification
* Lock/Unlock Animation
* Security Lockout Timer

*(Add screenshots or videos here.)*

---

# 🚀 Future Improvements

* OTP delivery via GSM or Wi-Fi
* Fingerprint sensor integration
* RFID authentication
* Bluetooth mobile application
* EEPROM password storage
* Servo motor for physical lock control
* Real-Time Clock (RTC) for timestamp logging
* IoT-based remote monitoring

---

# 📚 Learning Outcomes

* STM32 GPIO programming
* Register-level peripheral configuration
* Matrix keypad interfacing
* LCD interfacing
* Embedded C programming
* Modular firmware development
* State machine implementation
* Embedded security concepts
* User interface design for embedded systems

---

# 👨‍💻 Author

**Harsh Nayakal**
Final-Year Mechatronics Engineering Student

**Interests:**

* Embedded Systems
* Internet of Things (IoT)
* PCB Design
* STM32 Development
* Robotics
* Industrial Automation

---

# 📄 License

This project is released under the **MIT License**. Feel free to use, modify, and distribute it with proper attribution.

⭐ If you found this project useful, consider giving the repository a **star** on GitHub!
