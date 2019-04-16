@0x921325d841eeb3b5;

struct EventData {
   topic  @0 : Text;
   time   @1 : UInt64;
   event  @2 : Text;
   params @3 : List(Param);

   struct Param {
      key   @0 : Text;
      value @1 : Text;
   }
}

interface Event{
        emit @0 (eventData: EventData ) -> ();
}
