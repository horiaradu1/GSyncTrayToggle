# GSyncTrayToggle

A simple Windows tray app for toggling NVIDIA G-SYNC modes (Off / Fullscreen / Fullscreen + Windowed) using NVAPI.

---

## What It Does

- Adds a tray icon that shows your current G-SYNC mode.
- Lets you change G-SYNC mode from the tray menu, with NVIDIA's NVAPI.

---

## Project Structure

```
├── resources/              # Icon files for tray display
├── CMakeLists.txt          # Build config
├── GSyncTrayToggle.cpp     # Main tray logic
├── GSyncTrayToggle.rc      # Resource file (icons)
├── main.cpp                # NVAPI test/debug tool
├── resource.h              # Icon identifiers
└── settings.cpp            # Archived logic for reading raw settings
```
---

## References

- [🔗 NVAPI Get Started Guide (NVIDIA)](https://developer.nvidia.com/rtx/path-tracing/nvapi/get-started)
- [🔗 NVAPI GitHub (NVIDIA)](https://github.com/NVIDIA/nvapi)
- [🔗 NVAPI Official Docs](https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/)
- [🔗 StackOverflow – Accessing Global Profile Settings](https://stackoverflow.com/questions/43526033/problems-retrieving-the-global-profile-settings-shown-in-the-nvidia-control-pan)

---

## Notes

- `main.cpp` contains code for testing basic NVAPI functionality.
- `settings.cpp` holds older experiments for inspecting raw settings — kept for reference.
- Icons are dynamically updated based on your current G-SYNC state.
