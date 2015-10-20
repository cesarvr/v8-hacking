# v8-hacking
My first steps hacking the V8 Javascript engine. I want to learn how to interact native code with the V8 VM.

This is just a hello world example from [Google Developer] page with some modification cause the example 
provided there doesn't work out of the box for me.

instruction tested only in linux.

 * download the source code from https://developers.google.com/v8/build. 
 
* build/installing:

```sh
$ git clone git@github.com:cesarvr/v8-hacking.git
```
 - go to deps folder and make a symlink to your v8 folder, you can clone the v8 project inside, but I choose to make a soft link.

```sh
$ ln -s path/v8 deps/v8
```
* In root directory you can find the Makefile with a basic configuration to compile and link C++ with a Embedded V8. 
* this is just a hello world with C++ program with V8 embedded. to build it just do: 

```sh
make hello
```

* in this example I just create a native method [ print ], and exposure them in javascript so you can write something like:

```javascript
function(){
 print('hello world');
}
```

to compile it just do: 

```sh
make native
```


- happy hacking!.
- 
[Google Developer]: <https://cesarvr.github.io>
