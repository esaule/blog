---

title:  "Making a tiny titan case"
tags: [woodworking, work, en, 3617mylife]
---

So we have this project at work where we want to have a cluster of
NVIDIA Jetson that we use for demos. The intent of the demo is to
explain what parallel computing and HPC is, why you would care, why it
is important research. This could be demo for visiting students, or
demos in class, or just for when we have visitors. So the crux of the
demo is a cluster of Jetson that run some applications that we talk
over as it shows stuff that it can do.

Because there is a mobility question we can't house it in a permanent
case, we need to be able to move it around. So to get us started I
decided to build a prototype case out of wood that we can mount using
french cleats.

We call it tiny titan as a placeholder (which is still place holding)
because it started as a replication of ORNL project of the same name.

## Design

The cluster is 9 NVIDIA Jetson. They are interconnected by
Ethernet. The Jetsons have a USB LED connected to them so we can color
code devices. So we need space to house the Jetsons in a place where
airflow won't be a problem, and we can see the devices at work. We
also need to house all the power supplies which are kind of big. And
we need to house an Ethernet switch and powerstrips. We also need to
have ways to route cables: power, ethernet, and a display.

So after discussion, we ended up with this design which mounts the
cluster on a wall like a picture frame:

![Tiny Titan display design]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240802_162111081.jpg )

The Jetsons will be housed in "shelves" with a lip and a brace so that
they can't fall. The brace need to be removable so that we can access
the devices if we need to. Also it should make the fans and lights on
the Jetson visible. We will put three per shelf to build a 3x3 grid
which could be useful when we demo spatial problems.

Now the shelves need to be mounted to a backing board for easy
transportation. The shelves though be offseted away from the backing
board to enable routing network and power cables. The space behind the
shelves can also be used for hiding long and unruly cables.

After playing with configurations we decided on power and network
above it all.

## Building it

### Shelves

Most of the project is built with 1/2 inch plywood. The shelf has a
backing board which is plywood, with a small shelf. The shelves will
be backed off from the main project backing board by a strip of
plywood on each side.on each side, the edges of the shelves will serve
to prevent the board to fall on the side and to mount the brace. The
design is here:

![Shelf design]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240824_111301488.jpg )

The lip and the brace will be off smaller plywood (1/8 in IIRC). So A
dry run looks like that:

![Shelf dry run]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240824_1113226257.jpg )

Time for a glue up:

![Shelf glue up]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240824_123209146.jpg )

I was unclear how I would make the brace removable. I decided not to
worry about it at that point. I thought a machine screw with a insert
was probably best. In the end, I went for velcro, it proved reliable
and much easier to install

### Power brick storage

The power bricks on the Jetson are huge: they might be bigger than the
Jetson itself, which is a bit silly. I opted for having a bin on top
of the shelves that would house all the bricks. It has to be a bit
more voluminous. And I pierced three square(-ish) holes in them to
navigate the cabling around.

![Storing Power Bricks]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240825_150544740.jpg )

### Backing board

The rest is pretty simple you set mounting screws for the power strips
and the network switch. And you screw the shelves from the back of the
backing board. You can see the set up with a single board in here.

![Backing]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240825_150600016.jpg )


### Acrylic case

The original plan was to have an acrylic box to close the
display. Since the cluster is meant to be housed on a wall in a public
space, we were a bit worried putting people their hands in them and
messing it up.

So I cut some acrylic sheet to make a box. The guy at lowes
recommended some kind of caulk to glue it. And that works fine
letting me dry run the case.

![Some caulk]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240831_220549179.jpg )

![Dry run case]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240901_103801336.jpg )

I learned a
few things. 1/4 in acrylic is too flimsy. Caulk isn't the way to glue
acrylic. (Apparently there is acrylic cement which fuses pieces of
acrylic together; that sounds dope.) And finally. if you drill in
acrylic, you MUST have sacrificial piece of wood in front and behind
the acrylic.

So you guessed it right, I blew the acrylic case mounting it. So we
won't be doing that.

## Base

The project will be mounted on a wall. But we wanted to integrate the
base in the building design so that it blends in. So I built a base
for it to fasten to the wall with a French cleat on the back that will
be used to mount it.

It's straightforward to do in plywood. And a couple coats of spray
paint later, it is good to go.

![Base pre-paint]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240901_131332090.jpg )

![Base post-paint]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240901_132019079.jpg )

## Mounting

Putting everything together is pretty easy at this point.

Fasten the base to the wall.

![Mounting the base]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240901_162417102.jpg )

Putting the devices in for a test run from a table.

![Test run]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240902_152202996.jpg )

And finally deploying to the wall.

![Test run]({{site.baseurl}}/data/documents/woodworking/2024-08-tiny-titan/IMG_20240903_182542932.jpg )

You can see on that last picture that we ended up with plywood on the
edge and just a piece of acryclic to close the front of the case. You
can still theoretically pull things from the top but that's probably
fine; you'll have to be pretty committed.

The cluster is running a basic simulation of fluid dynamics. It shows
which device runs which part of the calculation by mathcing the
colors. Pretty cool!

## After thoughts

How long did the whole thing take? The design was decided August
2nd. And the installation was Sep 3. So it took about a month of real
time. But that wasn't that much time of work time. It took one day to
reach a shelf design that worked and to build the shelves. It took one
day to make the power brick box and set up the mounts for the power
strips and the switch. It took one day to build and screw up the
acrylic box. And one day to build the base, mount, and install. In
actual time of work, it is more like 2 days.

I did learn a thing or two while doing it. Pre-planning was
critical. And even like that, we still missed things like how tight
the cabling was going to be. I learned that you don't improvise
working with a new material (here acrylic) when you are on a project
you have to deploy.

In term of the build, Inserts are flimsy... French cleats work
everywhere.

About power. even with 9 power bricks, it doesn't get as hot as you
would think. It's warm, not hot. I do wonder whether there are power
bricks that have many output lines rather than having a brick for each
device. That would make the build much easier to manage. Overall, that
was pretty fun! I'd build another one!