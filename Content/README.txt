Garbage Collection: For UObject pointers (including pointers to classes that derive from UObject), Unreal Engine's garbage collection system handles memory management. You do not need to manually delete these objects. Instead, you should use smart pointers (TWeakObjectPtr, TSoftObjectPtr, etc.) or the UPROPERTY macro to ensure proper garbage collection.



In Unreal Engine, if you create pointers to UObject-derived classes without using UPROPERTY, those pointers will not be managed by the Unreal Engine Garbage Collection system. This means that:

Unreal Engine will not be able to track these pointers for automatic garbage collection, which can lead to dangling pointers if the objects are destroyed.
The object might be garbage-collected while the pointer still exists, causing crashes or undefined behavior when you try to access it.

Naked pointers (i.e. ones that are not declared with UPROPERTY) are not nulled out when they get collected by the Unreal's garbage collector.


To reference an object you have to store a pointer to it marked as a UPROPERTY in another live object. I


const 




	FItemData itemData; in the interface

If your game requires distinct HUD elements for different modes or states (e.g., a menu screen versus an in-game HUD),

UDamageType* dmgType;

vs

UClass* DamageType;

vs 

TSubclassOf<UDamageType> DamageType;
so the first one is an object pointer, and the last 2 are class pointers, and the final one is a specific type of class pointer than narrows down the list of available class choices.

class pointers are different from object pointers, because UClass pointers reference class assets available in the editor, while object pointers can only be valid at runtime, because they can only reference objects that are already created or spawned into ram during gameplay.


Assets used: 


https://opengameart.org/content/sara-16x18