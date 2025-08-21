# GSyncTrayToggle

A simple Windows tray app for toggling NVIDIA G-SYNC modes (Off / Fullscreen / Fullscreen + Windowed) using NVAPI.

---

## What It Does

- Adds a tray icon that shows your current G-SYNC mode.
- Lets you change G-SYNC mode from the tray menu, with NVIDIA's NVAPI.
- Icons are dynamically updated based on your current G-SYNC state.

| Tray Icon                                                                                            | Tooltip                         |
| ---------------------------------------------------------------------------------------------------- | ------------------------------- |
| <img src="resources/gsync_off.ico" width="32" height="32" alt="G-SYNC Off">                          | `G-SYNC: Off`                   |
| <img src="resources/gsync_full.ico" width="32" height="32" alt="G-SYNC Fullscreen Only">             | `G-SYNC: Fullscreen Only`       |
| <img src="resources/gsync_fullwindow.ico" width="32" height="32" alt="G-SYNC Fullscreen + Windowed"> | `G-SYNC: Fullscreen + Windowed` |


## Try it

Download the latest pre-built `.zip` from the Releases page:  
[https://github.com/horiaradu1/GSyncTrayToggle/releases](https://github.com/horiaradu1/GSyncTrayToggle/releases)

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

- [NVAPI](https://developer.nvidia.com/rtx/path-tracing/nvapi/get-started)
- [NVAPI GitHub (NVIDIA)](https://github.com/NVIDIA/nvapi)
- [NVAPI Docs](https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/)
- [StackOverflow – NVIDIA Global Profile inspiration](https://stackoverflow.com/questions/43526033/problems-retrieving-the-global-profile-settings-shown-in-the-nvidia-control-pan)

---

## Notes

- `main.cpp` contains code for testing basic NVAPI functionality.
- `settings.cpp` holds older experiments for inspecting raw settings — kept for reference.
