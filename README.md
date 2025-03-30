# KDE integration for Filotimo

WIP

## Brainstorm architecture
- Library component - abstracts over `rpm-ostree`/`bootc`, as well as `mokutil` or something else that's not as bad
    - Abstracts `rpm-ostree` for:
        - Rebasing an image
        - Detecting layered packages, allowing their removal using `rpm-ostree reset` (installation is out of scope)
        - Applying an usroverlay
        - Detecting if user booted into a rolled back image, and allowing image rollbacks
        - Listing and changing kernel arguments
    - Abstracts `mokutil` for:
        - Detecting if secure boot key is correctly enrolled
        - Enrolling the correct key
    - Also have a thingy that lists non-optimal system state for the KCM and Notifier to use
    
- System Administration KCM component - interfaces with the above library to:
    - Show a big old banner telling you if your system is OK or there's some sort of weird state that needs to be addressed, and list reasons
    - Allow you to easily switch branches if you e.g. need NVIDIA support - suggest to the user if they should do so
    - Reset layering
    - Apply an usroverlay (would be named Developer Mode)
    - List details on current and previously booted image
        - Also detect if the user booted into a previous image, ask them if they want to rollback and suggest to open an issue
    - List kernel arguments, provide a page to change these (obviously with disclaimers and warnings)
    - Allow the installation of a KDE development environment through a graphical interface (just make it launch Konsole with the associated `ujust`)

- Notifier component (user systemd service) - interfaces with the above library to:
    - Warn the user if secure boot key is not enrolled properly - prompt to open KCM
    - Warn the user if they would be better served by the NVIDIA image - prompt to open KCM
    - Notify the user that they're in the previous image - ask if they want to rollback - prompt to open KCM
