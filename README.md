# Check offline if your password was pwned

## Instructions

  * Fetch the password lists from <https://haveibeenpwned.com/Passwords>
  * Run `./merge`. The resulting file is a big sorted array of unique binary sha-1 hashes,
    it should be a multiple of 20 bytes. For me it's 6,405,889,280 bytes.
  * The .7z files can be removed.
  * Run `make`, requires gcc and openssl-dev to be installed.
  * For each password to check, run `./checkpw`, enter the password (plain text, not sha-1), press return.
  * If the output is "Found", your password was pwned.
