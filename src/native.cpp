#include <iostream>

#include "include/libplatform/libplatform.h"
#include "include/v8.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
  #include "tools.h"
}



using namespace v8;

// native endpoint
v8::Handle<v8::Context> CreatePlugins(v8::Isolate* isolate);


/* Variadic template for printing value */
void Print() {
  std::cout << std::endl;
}

template <typename T> void Print(const T& t) {
  std::cout << t << std::endl;
}


template<typename First, typename... Args> 
void Print(const First& first,  const Args&... args){
  
  Print(first);
  Print(args...);
}

/* */

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
  public:
    virtual void* Allocate(size_t length) {
      void* data = AllocateUninitialized(length);
     return data == NULL ? data : memset(data, 0, length);
    }

    virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
    virtual void Free(void* data, size_t) { free(data); }
};


void vm(Isolate *isolate, char *jsFile){
    Isolate::Scope isolate_scope(isolate);

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    // Create a new context.
    Local<Context> context = CreatePlugins(isolate);

    // Enter the context for compiling and running the hello world script.
    Context::Scope context_scope(context);

    // Create a string containing the JavaScript source code.
    Local<String> source =
        String::NewFromUtf8(isolate, jsFile,
                            NewStringType::kNormal).ToLocalChecked();

    // Compile the source code.
    Local<Script> script = Script::Compile(context, source).ToLocalChecked();

    // Run the script to get the result.
    Local<Value> result = script->Run(context).ToLocalChecked();

    // Convert the result to an UTF8 string and print it.
    String::Utf8Value utf8(result);
    Print(" result --->", *utf8);
}

int main(int argc, char *argv[]){

  if (argc != 2) {
    printf("usage: %s Javascript file. \n", argv[0]);
    exit(0);
  }

  // Initialize V8.
  V8::InitializeICU();

  Platform* platform = platform::CreateDefaultPlatform();
  V8::InitializePlatform(platform);
  V8::Initialize();

  // Create a new Isolate and make it the current one.
  ArrayBufferAllocator allocator;
  Isolate::CreateParams create_params;
  create_params.array_buffer_allocator = &allocator;
  Isolate* isolate = Isolate::New(create_params);

  char *jsFile = NULL; 

  jsFile = readFile(argv[1]);
  printf("js-> %s", jsFile);
  vm(isolate, jsFile); 

  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  V8::Dispose();
  V8::ShutdownPlatform();
  delete platform;

  //return allocated memory.
  free(jsFile);

  return 0;
}



/* 
 * Definition of the NativeContext. 
 */

v8::Handle<v8::Context> CreatePlugins(v8::Isolate* isolate) {
  v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
  

  global->Set(v8::String::NewFromUtf8(isolate, "print"),
              v8::FunctionTemplate::New(isolate, Print));

  
  return v8::Context::New(isolate, NULL, global);
}







