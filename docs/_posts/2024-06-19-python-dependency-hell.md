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

I've been told you should upgrade pip first

```bash
$ pip install --upgrade pip
```

and from there, you have an empty python environment. so anything you do is from a clean slate. So you can install packages or force a particular package version with pip pretty easily:
```bash
$ pip install Flask==1.1.2
$ pip install wget==3.2
```

The point of it is that you'll eventually can generate a list of
precise requirements once you get teh code working with `pip freeze >
requirements.txt`. So that in production environment you can install
these particular versions of the pacakges so that your production and
dev environments are synchronized. You can do that with `pip install
-r requirements.txt`.

## Python interpretor hell

I set all the pacakges in the same version as in production, let's run the code again... and I get:

```ImportError: cannot import name 'Mapping' from 'collections' (/usr/lib/python3.10/collections/__init__.py)```

And this is where, I descend into insanity. No one seems to care in
the python team about backwards compatibility. What happens is that my
linux distribution has a python 3.10 installed but when the code was
developped the interpretor was in version 3.8. and in between these two versions, the name of the object hs changed (as noted in [this stack overflow post](https://stackoverflow.com/questions/69381312/importerror-cannot-import-name-from-collections-using-python-3-10 ) ).

So now, I only have two options. 1. Try to upgrade an application that
as far as I know doesn't work to python 3.10 with dependencies and
all. 2. Or install an old version of python. And rebuild the
environment against that. Let's do that. (Somewhere on the web, we
find people saying you can do that with simply `pip install
python==3.8` but that doesn't work for me, and search the pip website
for python returns a bazillion match. so if it has changed name, I
can't find it.)

[This blog post](
https://ruan.dev/blog/2022/06/23/install-a-specific-python-version-on-ubuntu
) has a run down on how to do that. It is done in a bit of a stupid
way because it install to system wide instead of installing in `/opt`
or something. Why `/opt`? check [FHS](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard )!

```bash
$ sudo apt install build-essential libssl-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm libncurses5-dev libncursesw5-dev xz-utils tk-dev libffi-dev liblzma-dev python3-openssl git # to install dependencies
$ cd ~/prgs # I do all my local compilations in ~/prgs/
$ wget https://www.python.org/ftp/python/3.8.10/Python-3.8.10.tgz
$ tar -xvf Python-3.8.10.tgz
$ cd Python-3.8.10/
$ ./configure --enable-optimizations --prefix=/opt/python-3.8.10 # --prefix let's you chose where the software install, /opt is for the things you install yourself (essentially)
$ make -j 12 # -j 12 uses 12 processes to compile which somehow is not default in make
$ sudo make install
```

We can check that it worked by creating a BS environment somewhere:

```bash
$ mkdir ~/foobar
$ cd ~/foobar
$ /opt/python-3.8.10/bin/python3.8 -m venv something
$ . ./something/bin/activate
(something) $ which python
/home/erik/foobar/something/bin/python
(something) $ python3
Python 3.8.10 (default, Jun 19 2024, 20:28:04) 
[GCC 11.4.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> 
(something) $ which pip
/home/erik/foobar/something/bin/pip
(something) $ pip --version
pip 21.1.1 from /home/erik/foobar/something/lib/python3.8/site-packages/pip (python 3.8)
```

Everything seems in order! I should now be able to rebuild the virtual
environment for that particular project.


## Rebuilding env

```bash
$ cd $project
$ rm -rf myvenv/ #remove previous environment
$ /opt/python-3.8.10/bin/python3 -m venv myvenv #recreate environemnt against python 3.8
$ . ./myvenv/bin/activate
$ pip install Flask==1.1.2 #reinstall packages
$ pip install Jinja2==2.10.1
$ pip install MarkupSafe==1.1.0 Werkzeug==1.0.1
```

And after a couple more missing packages, I can finally run the flask
app. It runs. I try the route that killed it. And... that works too.

So now I can generate the requirements.txt with:

```bash
$ pip freeze > requirements.txt
```

So in a production environment you should be able to do:

```bash
$ /opt/python-3.8.10/bin/python3 -m venv myvenv #recreate environemnt against python 3.8
$ . ./myenv/bin/activate
$ pip install -r requirements.txt
```

(Assuming python is in the same place. Or one can recompile python in the user account somewhere)

## So... What's the problem again?

Well, now I have another problem. The application runs in my testing
environemnt but not in production. What's going on? I bet I ran out of
disk space. Did I run out of disk space?

```bash
$ ssh prodserver
$ df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/root        49G   49G     0 100% /
```

Yep...
