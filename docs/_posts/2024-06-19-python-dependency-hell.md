---

title:  "Figuring out python dependency hell"
tags: [programming, geek, en]
---


I find myself trying to figure out a python dependency hell. So as I
am trying to figure this out properly for the first time, I thought,
I'd take some notes as I do it so that I can points colleagues to
later. And maybe myself. For context, there is a webservice I maintain
now which I didn't write (do we ever?). It was written by a student a
bazillion years ago. (I just checked, the last git commit was July
2021, but the main development was July 2020.)

I won't tell which code I am looking at in particular to avoid
embarassing a student who wrote that as they were learning how any of
this goes and who has long graduated. So obviously the code is not
particularly good shape. The documentation for installation is
literaly "you need python and these 2 packages". And that's it.

It seems that I did deploy that code on an EC2 instance a WHILE
back. And it used to work. I have logs that show that it did work
until a few weeks ago. And now it doesn't and I don't have any idea
why. So the first thing I'd like to do is run it locally.

I pip install the few packages the documentation asks for. and nothing
runs. Obviously I have a python dependency hell.

Before I go further. Let me clearly state that I am no devops and
barely a function python developer. So, I may say a ton of non-sense. Let me know.

## On virtual env

Alright, it seems like I'm gonna have to install some quite old
packages. So first let's set up a virtual environment. Documentation
is [here](https://docs.python.org/3/library/venv.html). But the basics
are basically
[here](https://www.freecodecamp.org/news/python-requirementstxt-explained/).

It boils down to installing the virtual env the first time with

```bash
$ python3 -m venv myvenv
```

Then in your session (and in each of your terminal sessions), you would activate it with
```bash
$ . ./myvenv/bin/activate
```

and from there, you have an empty python environment. so anything you do is from a clean slate. So you can install packages or force a particular package version with pip pretty easily:
```bash
$ pip install --upgrade pip
$ pip install Flask==1.1.2
$ pip install wget==3.2
```

The point of it is that you'll eventually can generate a list of
precise requirements once you get teh code working with `pip freeze >
requirements.txt`. So that in production environment you can install
these particular versions of the pacakges so that your production and
dev environments are synchronized. You can do that with `pip install
-r requirements.txt`.