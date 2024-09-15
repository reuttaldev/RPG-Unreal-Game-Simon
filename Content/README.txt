Garbage Collection: For UObject pointers (including pointers to classes that derive from UObject), Unreal Engine's garbage collection system handles memory management. You do not need to manually delete these objects. Instead, you should use smart pointers (TWeakObjectPtr, TSoftObjectPtr, etc.) or the UPROPERTY macro to ensure proper garbage collection.


	FItemData itemData; in the interface