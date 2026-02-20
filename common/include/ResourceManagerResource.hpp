#pragma once

#include <string>

struct ResourceManagerResource {
	template<typename T>
	ResourceManagerResource(T* resourceIn) : resource(resourceIn),
		deleterFunction([](ResourceManagerResource* this_, void* res) {delete static_cast<T*>(this_->resource); })
	{
	}

	~ResourceManagerResource() {
		deleterFunction(this, resource);
	}

	void* resource;
	void (*deleterFunction)(ResourceManagerResource*, void*);
};

using Resource = ResourceManagerResource;
