# Marlo
Markdown parser written in c

## install

```
$ git clone https://github.com/PaprPlane/marlo.git
$ cd marlo
$ make
```

## Todo

- [x] make function for reading chains of chars
- [ ] generate html
  - [x] blank lines (`===`,`---`)
  - [x] headings (`#`)
  - [x] bold (`** x **`)
  - [x] italic (`*** x ***`)
  - [ ] code (``` ` ```);
  - [ ] tables (`---|---|---`)

- [ ] code things
    - [ ] fix bug where heading tags are not closed
    - [ ] add code for parsing commands than need to be more than one
          char long
