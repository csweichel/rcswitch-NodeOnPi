#include <v8.h>
#include <node.h>

#include "../externals/rcswitch-pi/RCSwitch.h"

using namespace v8;

class RCSwitchNode : node::ObjectWrap {
  private:
    RCSwitch rcswitch = RCSwitch();

    #define switchOp2(p1, p2) { if(switchOn) thiz->rcswitch.switchOn((p1), (p2)); else thiz->rcswitch.switchOff((p1), (p2)); }
    #define switchOp3(p1, p2, p3) { if(switchOn) thiz->rcswitch.switchOn((p1), (p2), (p3)); else thiz->rcswitch.switchOff((p1), (p2), (p3)); }
    static v8::Handle<Value> SwitchOp(const Arguments& args, bool switchOn) {
      v8::HandleScope scope;
      RCSwitchNode* thiz = node::ObjectWrap::Unwrap<RCSwitchNode>(args.This());
      
      v8::Handle<Value> result = v8::Boolean::New(false);
      if(args.Length() == 2) {
        v8::Handle<v8::Value> group = args[0];
        v8::Handle<v8::Value> swtch = args[1];

        if(group->IsInt32() && swtch->IsInt32()) {
          switchOp2(group->Int32Value(), swtch->Int32Value());
          result = v8::Boolean::New(true);
        } else if(group->IsString() && swtch->IsInt32()) {
          v8::String::AsciiValue sGroup(group);

          if(sGroup.length() >= 5) {
            switchOp2(*sGroup, swtch->Int32Value());
            result = v8::Boolean::New(true);
          }
        }
      } else if(args.Length() == 3) {
        v8::Handle<v8::Value> famly = args[0];
        v8::Handle<v8::Value> group = args[1];
        v8::Handle<v8::Value> devce = args[2];

        if(famly->IsString() && group->IsInt32() && devce->IsInt32()) {
          v8::String::AsciiValue v8str(famly);

          if(v8str.length() > 0) {
            switchOp3(*(*v8str), group->Int32Value(), devce->Int32Value());
            result = v8::Boolean::New(true);
          }
        }
      }

      return result;
    }

  public:
    RCSwitchNode() { }
    ~RCSwitchNode() {}
    
    static v8::Persistent<FunctionTemplate> persistent_function_template;

    static void Init(Handle<Object> target) {
      if( wiringPiSetup() == -1 ) {
        ThrowException( Exception::TypeError( String::New( "GPIO initialization failed" ) ) );
        return;
      }
      v8::HandleScope scope;

      v8::Local<FunctionTemplate> local_function_template = v8::FunctionTemplate::New(New);
      RCSwitchNode::persistent_function_template = v8::Persistent<FunctionTemplate>::New(local_function_template);
      RCSwitchNode::persistent_function_template->InstanceTemplate()->SetInternalFieldCount(1); // 1 since this is a constructor function
      RCSwitchNode::persistent_function_template->SetClassName(v8::String::NewSymbol("RCSwitch"));
      
      RCSwitchNode::persistent_function_template->InstanceTemplate()->SetAccessor(String::New("protocol"), GetProtocol, SetProtocol);
      
      NODE_SET_PROTOTYPE_METHOD(RCSwitchNode::persistent_function_template, "send", Send);
      NODE_SET_PROTOTYPE_METHOD(RCSwitchNode::persistent_function_template, "enableTransmit", EnableTransmit);
      NODE_SET_PROTOTYPE_METHOD(RCSwitchNode::persistent_function_template, "disableTransmit", DisableTransmit);
      NODE_SET_PROTOTYPE_METHOD(RCSwitchNode::persistent_function_template, "switchOn", SwitchOn);
      NODE_SET_PROTOTYPE_METHOD(RCSwitchNode::persistent_function_template, "switchOff", SwitchOff);
      
      target->Set(String::NewSymbol("RCSwitch"), RCSwitchNode::persistent_function_template->GetFunction());
    }

    static Handle<Value> New(const Arguments& args) {
      HandleScope scope;
      
      RCSwitchNode* rcswitchNode_instance = new RCSwitchNode();
      rcswitchNode_instance->Wrap(args.This());
      
      return args.This();
    }

    static v8::Handle<Value> Send(const Arguments& args) {
      v8::HandleScope scope;
      
      RCSwitchNode* rcswitchNode_instance = node::ObjectWrap::Unwrap<RCSwitchNode>(args.This());
      
      v8::String::Utf8Value v8str(args[0]);
      rcswitchNode_instance->rcswitch.send(*v8str);

      return v8::Boolean::New(true);
    }

    // notification.enableTransmit();
    static v8::Handle<Value> EnableTransmit(const Arguments& args) {
      v8::HandleScope scope;
      RCSwitchNode* rcswitchNode_instance = node::ObjectWrap::Unwrap<RCSwitchNode>(args.This());
      
      v8::Handle<v8::Value> pinNr = args[0];
      if(pinNr->IsInt32()) {
        rcswitchNode_instance->rcswitch.enableTransmit(pinNr->Int32Value());
        return v8::Boolean::New(true);
      } else {
        return v8::Boolean::New(false);
      }
    }

    // notification.disableTransmit();
    static v8::Handle<Value> DisableTransmit(const Arguments& args) {
      v8::HandleScope scope;
      
      RCSwitchNode* rcswitchNode_instance = node::ObjectWrap::Unwrap<RCSwitchNode>(args.This());
      rcswitchNode_instance->rcswitch.disableTransmit();
      return v8::Boolean::New(true);
    }

    static v8::Handle<Value> SwitchOn(const Arguments& args) {
      SwitchOp(args, true);
    }
    static v8::Handle<Value> SwitchOff(const Arguments& args) {
      SwitchOp(args, false);
    }

    // notification.protocol=
    static void SetProtocol(Local<String> property, Local<Value> value, const AccessorInfo& info) {
      RCSwitchNode* rcswitchNode_instance = node::ObjectWrap::Unwrap<RCSwitchNode>(info.Holder());

      if(value->IsInt32())
        rcswitchNode_instance->rcswitch.setProtocol(value->Int32Value());
    }
    
    // notification.protocol
    static v8::Handle<Value> GetProtocol(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
      RCSwitchNode* rcswitchNode_instance = node::ObjectWrap::Unwrap<RCSwitchNode>(info.Holder());
      return v8::Uint32::New(rcswitchNode_instance->rcswitch.getReceivedProtocol());
    }
};

v8::Persistent<FunctionTemplate> RCSwitchNode::persistent_function_template;
extern "C" {
  static void init(Handle<Object> target) {
    RCSwitchNode::Init(target);
  }
  NODE_MODULE(rcswitch, init);
}
