# Magical 8bit Plug 2
By Yokemura @ [YMCK](http://ymck.net/)

Magical 8bit Plug is a software synthesizer to generate the tones like the old 8bit game consoles.

Naming "2" of course means there was the first version, but the code base of it is already obsolate and hard to maintain, so this version is developed from scratch with only very little code snippet brought from the previous version.

Upon rewriting from scratch I set the base to [JUCE](https://juce.com/). Thanks to this awesome framework I was able to build it fast and able to add more functionality than the previous version.



# Getting Started

To build from the source:

- Get [Projucer](https://shop.juce.com/get-juce) (JUCE IDE)
- Setup your native development environment(ex. XCode for Mac, VisualStudio for Windows)
- Open magical8bitPlug2-juce.jucer with Projucer
- Select the native IDE and export
- Build

# License

This software is released under GPL v3 license.

Although this plugin satisfies the condition of JUCE's [Personal License](https://juce.com/juce-5-license), I chose GPL by my own decision. This is sort of a backup for me just in case it breaks that condition. As the plugin is a not a kind of library that can be a core part of other product, I believe there will be very little concern about "copyleft contamination".
In other words, my choice is not based on a strong belief on the copyleft and it can be changed if there are any positive reason to do that.

See [LICENSE](./LICENSE) for details.

# Donation

You can support developing Magical 8bit Plug not only by the contribution of source code but by the donation as well. We really appreciate your support.

[![](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=5CKQFPFTHRNMS)

<div class="donate">
<form action="https://www.paypal.com/cgi-bin/webscr" method="post">
<input type="hidden" name="cmd" value="_donations">
<input type="hidden" name="business" value="5CKQFPFTHRNMS">
<input type="image" src="http://www.ymck.net/images/download/btn_donate.png" border="0" name="submit" alt="Donate" formtarget="_blank">
</form>
</div>
