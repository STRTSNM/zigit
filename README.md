# Zigit

<div align="center">
  <img src="https://github.com/user-attachments/assets/8a8942a3-8310-48fe-ae47-740076e29696" alt="zigit-logo">


*Zigit* is a superfast GitHub repository downloader written in C, using aria2c
</div>


---
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

## Usage

Clone a GitHub repository by running:
```bash
zigit clone https://github.com/user/repo
```
or 
## Flags
- Use the `-b` or `--branch` flag followed by the name of the branch to specify a branch. 
---
![Stars](https://img.shields.io/github/stars/STRTSNM/zigit?style=flat-square)
![License](https://img.shields.io/github/license/STRTSNM/zigit?style=flat-square)


## Future Improvements
- [X] Add an option to specify custom branch
- [ ] Add true clone support in git sense 
- [ ] Add progress bar for extraction
- [ ] Support for private repositories (via token)
