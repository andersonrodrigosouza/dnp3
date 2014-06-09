/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#ifndef __STATIC_QUEUE_H_
#define __STATIC_QUEUE_H_

#include "Configure.h"
#include <assert.h>

namespace openpal
{

template <class ValueType, class IndexType, IndexType N>
class StaticQueue
{

public:

	StaticQueue() : count(0), first(0), nextInsert(0)
	{}

	IndexType Size() const
	{
		return count;
	}	

	IndexType Capacity() const
	{
		return N;
	}

	bool IsEmpty() const
	{
		return count == 0;
	}

	bool IsNotEmpty() const
	{
		return count > 0;
	}

	bool IsFull() const
	{
		return count == N;
	}

	void Clear()
	{
		count = first = nextInsert = 0;
	}	

	ValueType& Peek()
	{
		assert(IsNotEmpty());
		return array[first];
	}

	ValueType& Pop()
	{
		assert(IsNotEmpty());
		IndexType ret = first;
		first = (first + 1) % N;
		--count;
		return array[ret];
	}

	bool Enqueue(const ValueType& value)
	{
		if (IsFull())
		{
			return false;
		}
		else
		{
			array[nextInsert] = value;
			nextInsert = (nextInsert + 1) % N;
			++count;
			return true;
		}
	}

private:

	IndexType count;
	IndexType first;
	IndexType nextInsert;
	

	ValueType array[N];
};

}

#endif
