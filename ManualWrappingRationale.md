# Introduction #

I'll try to explain some of the reasons why I started wrapping OSG manually, and why I'm continuing in this vein even now that I'm starting to see some disadvantages. Note that this document does not assert that I'll never switch to some automatic generation of wrappers if I ever start feeling like it's too much work to continue this way, it's just to explain why I'm doing it this way for now.

# Advantages #

  * **Control**: I can choose what to wrap and how to wrap it (do I want this getter/setter pair to form a property? do I want this method to be available at all?). I can also choose to ignore whole sections of the class hierarchy (as is the case with the [Array](http://www.openscenegraph.org/documentation/OpenSceneGraphReferenceDocs/a00026.html) family of classes - they're a pretty complex hierarchy, but wrapping them by ignoring all but the first and last level is easy). This also means that if there are opportunities for optimization, I can find them and implement them, whereas I'd have to go through more hoops if I were generating the wrappers through some tool.
  * **Familiarity**: I am a C++ programmer who wants to start prototyping/developing apps in python, not the other way around. So after having spent years programming OSG apps in C++, I feel right at home doing the wrapping in C++. Other solutions required that I learn another language (or do the wrapping in python, which would have been less comfortable for me).
  * **Adaptability**: (hard to find a good name for what I'll explain in this point) Automatic generation tends to have problems with some of what OSG does, be it the intrusive reference counting, protected destructors, passing polymorphic arguments by const reference, etc. The point about control I noted above also applies to these: All the code is right there, so if it doesn't work right I can change it. Which leads me to:
  * **Direct access**: There is no level of indirection between the wrapping code and the wrapper. It's one and the same. If at some point, the wrapper breaks, and say it's been a while since I've touched it, I just have to go to one place and re-read some code comments to know how to fix it. If I were to do automatic generation, not only would I have to re-familiarize myself with boost.python to know why it broke, but I'd have to re-learn the generation tool and its language as well to fix it.

I guess most of these just mean that I prefer a "close to the metal" approach.

# Disadvantages #

  * **Tedious**: Wrapping methods is often a repetitive task, which is of course a hint that some automatic generation would be a better choice. As a colleague noted, I'm starting to see the explosion of thin wrappers and function pointers needed to wrap the code. For example, when wrapping methods that have several overrides, like a getter that returns a non-const and a const pointer, I need a function pointer alias to disambiguate between the two and make sure I wrap the one I want.
  * **Incomplete**: By their nature, the wrappers will probably never be complete, and will take more work to keep up to date than simply re-running the generation tool. But this is a trade-off as I noted above.

# Comments welcome #

Please comment on this page if you have anything to mention. The content will surely evolve as I think of other pros/cons.