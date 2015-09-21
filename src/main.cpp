#include <iostream>

#include "include/libplatform/libplatform.h"
#include "include/v8.h"

#include <stdlib.h>
#include <string.h>


using namespace v8;

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

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
  public:
    virtual void* Allocate(size_t length) {
      Print("Allocating Memory-> ", length );  
      void* data = AllocateUninitialized(length);
     return data == NULL ? data : memset(data, 0, length);
    }
    virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
    virtual void Free(void* data, size_t) { Print("free! "); free(data); }
};


void exec(Isolate *isolate){
    Isolate::Scope isolate_scope(isolate);

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    // Create a new context.
    Local<Context> context = Context::New(isolate);

    // Enter the context for compiling and running the hello world script.
    Context::Scope context_scope(context);

    // Create a string containing the JavaScript source code.
    Local<String> source =
        String::NewFromUtf8(isolate, "'Hello' + ', World!'",
                            NewStringType::kNormal).ToLocalChecked();

    // Compile the source code.
    Local<Script> script = Script::Compile(context, source).ToLocalChecked();

    // Run the script to get the result.
    Local<Value> result = script->Run(context).ToLocalChecked();

    // Convert the result to an UTF8 string and print it.
    String::Utf8Value utf8(result);
    Print(" result --->", *utf8);
}

int main(){
  // Initialize V8.
  V8::InitializeICU();
  //V8::InitializeExternalStartupData(argv[0]);
  Platform* platform = platform::CreateDefaultPlatform();
  V8::InitializePlatform(platform);
  V8::Initialize();

  // Create a new Isolate and make it the current one.
  ArrayBufferAllocator allocator;
  Isolate::CreateParams create_params;
  create_params.array_buffer_allocator = &allocator;
  Isolate* isolate = Isolate::New(create_params);
  

  exec(isolate); 

  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  V8::Dispose();
  V8::ShutdownPlatform();
  delete platform;
  return 0;

}
