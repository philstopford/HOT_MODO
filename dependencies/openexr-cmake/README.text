IlmBase and OpenEXR for CMake
=============================

This is a custom bundle which builds IlmBase and OpenEXR together using [CMake](http://www.cmake.org/).
Although its main goal is to simplify the process of building Windows versions using Visual C++ it also
works on Linux and OSX. The sources are based on the 
[upstream OpenEXR](http://savannah.nongnu.org/projects/openexr/) version and incorporate some additional
Windows-motivated patches.

CMake build system by [Edgar Velázquez-Armendáriz](http://www.cs.cornell.edu/~eva5/).
It was originally created as part of [HDRITools](https://bitbucket.org/edgarv/hdritools/). 

About the IlmBase Libraries 
----------------------------

Half is a class that encapsulates our 16-bit floating-point format.

IlmThread is a thread abstraction library for use with OpenEXR
and other software packages.  It currently supports pthreads and
Windows threads.

Imath implements 2D and 3D vectors, 3x3 and 4x4 matrices, quaternions
and other useful 2D and 3D math functions.

Iex is an exception-handling library.

If you have questions about using the IlmBase libraries, you may want
to join our developer mailing list.  See [openexr.com](http://www.openexr.com) for
details.

About the OpenEXR Libraries
----------------------------

IlmImf is our "EXR" file format for storing 16-bit FP images.  Libraries in
this package depend on the IlmBase library.

See the IlmImfExamples directory for some code that demonstrates how
to use the IlmImf library to read and write OpenEXR files.  The doc
directory contains some high-level documentation and history about the
OpenEXR format.

If you have questions about using the OpenEXR libraries, you may want
to join our developer mailing list.  See [openexr.com](http://www.openexr.com) for
details.

Building
--------

To generate the build files using `cmake` one can just execute, 
from the directory where the build files will be created: 

    $ cmake -G "Generator Name" PATH_TO_SOURCE

Where `Generator Name` is the name of the desired generator as shown by 
executing `cmake` without arguments. `PATH_TO_SOURCE` is the path (relative
or absolute) to the directory where the `CMakeLists.txt` file at the top of
the sources is located. More details about how to invoke cmake may be consulted
in its online [documentation](http://www.cmake.org/cmake/help/runningcmake.html).

License
-------

The IlmBase and OpenEXR source code distributions are free software, distributed
under the Modified BSD License.

> Copyright (c) 2006, Industrial Light & Magic, a division of Lucasfilm
> Entertainment Company Ltd.  Portions contributed and copyright held by
> others as indicated.  All rights reserved.
>
> Redistribution and use in source and binary forms, with or without
> modification, are permitted provided that the following conditions are
> met:
>
> * Redistributions of source code must retain the above
>   copyright notice, this list of conditions and the following
>   disclaimer.
>
> * Redistributions in binary form must reproduce the above
>   copyright notice, this list of conditions and the following
>   disclaimer in the documentation and/or other materials provided with
>   the distribution.
>
> * Neither the name of Industrial Light & Magic nor the names of
>   any other contributors to this software may be used to endorse or
>   promote products derived from this software without specific prior
>   written permission.
>
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
> IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
> THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
> PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
> CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
> EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
> PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
> PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
> LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
> NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
> SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
