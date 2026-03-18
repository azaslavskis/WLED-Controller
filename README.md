# WLED Controller ⚡🌈

A compact ESP32-C3 based controller board for running addressable LED strips with **WLED** and integrating them into **Home Assistant**.

![Top view of board](https://github.com/user-attachments/assets/ace5ed26-4013-484a-8079-e882eb7c22a7)

---

## What this project includes

- **Hardware design files** (KiCad project, production outputs, 3D model assets)
- **Firmware patch helper** for building a patched WLED version
- **Assembly references** for the current controller revision

---

## ⚠️ Current hardware status

> **Do not order this PCB revision yet** — the board still has known issues.

### Known issues to fix before ordering

1. `R7` / `EN` pin of `XL1509-5.0V` should be connected to **GND**, not input.
2. ESP32-C3 **pin 9** must be pulled correctly for reliable boot.
3. `DS18B20` pin must be pulled to **3.3V** (fixed on rev **1.6**).
4. More physical spacing is needed for `C1`, `C3`, and `C9`.

---

## Assembled unit

![Assembled unit](https://github.com/user-attachments/assets/7e77cd1e-8eaa-4123-9331-6aaf47583ac2)

---

## Build patched firmware

Run the helper script directly:

```bash
wget https://raw.githubusercontent.com/azaslavskis/WLED-Controller/refs/heads/main/software/WLED-Git_patch/patch.sh \
  && chmod +x patch.sh \
  && ./patch.sh
```

---

## Repository layout (high level)

- `hardware/` → PCB project, exports, and fabrication artifacts
- `software/` → firmware patching/build helper files
- `3d-models/` → enclosure and mounting models

---

## Project goal

Create a reliable, DIY-friendly LED controller that is easy to deploy in smart-home setups and flexible enough for custom lighting projects.
