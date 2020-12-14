#!/bin/sh

# Source the environment variables stored in the `.env` file.
source .env

# Go to `configs` subdirectory.
cd configs

# -----------------

# Option A (testing): localize and do a two-way synchronization
# only with the translation service (i.e. Smartcat).
serge pull-ts localize push-ts

# ------ OR -------

# Option B (production): perform the full synchronization cycle
# both with your VCS repos and with the translation service.
#serge sync

# -----------------

# Clean up orphaned translation files (the ones that
# correspond to no longer existing source files). This command
# needs to be run against all configuration files at once.
serge clean-ts
