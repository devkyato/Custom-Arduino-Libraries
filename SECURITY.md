# Security policy

## Supported versions

Security fixes are provided for the latest release.

## Reporting a vulnerability

Please do not open a public issue for a suspected vulnerability. Use GitHub's
private vulnerability reporting feature on the repository's **Security** tab.
Include the affected version, board, a minimal reproduction, and the potential
impact. You should receive an initial response within seven days.

This library directly controls GPIO and does not process network input, but
memory-safety, unexpected pin-state, and denial-of-service findings are still
welcome.
