# Zigit

---
- Uses `aria2c` for fast, multi-connection downloads.

## Requirements

Make sure you have the following installed:

- **aria2**
- **unzip**
- **gcc** (or other equivalent compilers)

To install them on a Debian/Ubuntu system:

```bash
sudo apt install aria2 unzip gcc
```
To install them on an Arch system (i use arch btw ¯\(ツ)/¯ ) :
```bash
sudo pacman -Syy aria2 unzip gcc
```

## Installing zigit
```bash
make
make install
```
Usage
Clone a GitHub repository by running:
```bash
zigit clone https://github.com/user/repo
```
---
## License
This project is released under the MIT License.
Feel free to modify and distribute it.

## Future Improvements

- Add true clone support in git sense 

- Add progress bar for extraction

- Support for private repositories (via token)

- Option to specify custom branch
