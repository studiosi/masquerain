# Masquerain

Masquerain is a tool to convert images into Teletext stills, as per Teletext Level 1 standard. It is used on the command line, through a pretty simple interface.

## Usage

```
Options:
  -h [ --help ]         Shows Usage
  -i [ --input ] arg    Input File
  -o [ --output ] arg   Output File
```
The input and output files must be the full path. For example, typing
```
Masquerain.exe -i in.jpg -o out.jpg
```
Will convert in.jpg and save it as out.jpg and

```
Masquerain.exe --help
```
Will show the usage.

## Compilation

The executable has been compiled under Visual Studio 2015, using OpenCV 3.4.1 and Boost-Program-Options 1.66.0, as provided by VCPkg, the Microsoft packaging tool for Visual C++.

## Contributors

Contributors are more than welcome. If you have any idea that you want to implement to extend the software, just branch, code and create a pull request. Also the issues are open for feature requests.

## Shootouts

**Mistigris**, for spoiling my interest in teletext and other forms of text-art. 

**Ferris of Logicoma**, for providing so many hours of educational entertainment and so much good content in the shape of demos, music and other stuff. Also, for resuscitating my dormant interest on the demoscene and vintage systems.

## Examples

Three examples are included in the software package (all three original images are CC0), here they are:

### Apricots

![Apricots, original](https://github.com/studiosi/masquerain/blob/master/Examples/Apricots/apricots.jpg)
![Apricots, processed](https://github.com/studiosi/masquerain/blob/master/Examples/Apricots/apricots_ttx.jpg)

### Horizon

![Horizon, original](https://github.com/studiosi/masquerain/blob/master/Examples/Horizon/horizon.jpg)
![Horizon, processed](https://github.com/studiosi/masquerain/blob/master/Examples/Horizon/horizon_ttx.jpg)

### SkyHeart

![SkyHeart, original](https://github.com/studiosi/masquerain/blob/master/Examples/SkyHeart/skyheart.jpg)
![SkyHeart, processed](https://github.com/studiosi/masquerain/blob/master/Examples/SkyHeart/skyheart_ttx.jpg)

## License

Copyright 2018 David Gil de Gómez Pérez (Studiosi)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
