# sgit

A lightweight Git-like version control system written from scratch in C.
The name comes from combining scratch and git: sgit

## Disclaimer

In no way, shape, or form is this a viable replacement for Git. This is
only my attempt at creating something similar and learning how version
control systems work internally, Linux filesystem APIs, a bit of Bash
and C concepts such as: heap and stack memory, file I/O, data structures,
pointers, hashing, linked lists and trees, recursion and so on.

## How it works

Sgit does things very similarly to how Git does them. It divides its objects into 
3 categories: blobs (files), trees (directories), and commits (snapshots at a given time).
When an sgit repository is initialized, it creates a hidden directory called '.sgit'. Inside 
it, there is a file called 'HEAD', which stores the hash of the latest commit, and 
a directory called 'objects', which stores the data of the repository's blobs, trees and commits.
Sgit uses the DJB2 hashing algorithm to generate 32-bit unsigned integer hashes.

## Limitations

SGit has a lot of limitations. Here are a few of them: 

 * No staging area, every file is committed;
 * Only one branch;
 * Checkout loses commits from history, even though they still exist on disk; 
 * Simplified object format;
 * Hashing is not cryptographically secure and collisions are likely to happen;
 * Error handling is bad;
 * Only works on POSIX machines;
 * Memory management is not robust enough.

## sgit commands

 * sgit init - Creates the ".sgit" directory and its object storage
 * sgit commit "Message" - creates a snapshot of the directory you are in
 * sgit status - checks the state of the files: untracked, deleted,  modified
 * sgit log - view commit history: shows root tree hash, commit parent hash, time, date and message
 * sgit checkout <commit-hash> - restores the files from a previous commit

## Installation

    1. Clone the repository
    2. Install dependencies 'sudo xbps-install -S gcc bash'
    3. Build the bash file `./build.sh'
    4. Enjoy
