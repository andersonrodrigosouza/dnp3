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
#include "Database.h"

#include "MeasurementHelpers.h"

#include <assert.h>

#include <opendnp3/DNPConstants.h>


#include <openpal/LoggableMacros.h>

using namespace openpal;

namespace opendnp3
{

Database::Database(openpal::Logger aLogger, const StaticDataFacade& aStaticData) :
	Loggable(aLogger),	
	staticData(aStaticData)
{

}

bool Database::AddEventBuffer(IEventBuffer* apEventBuffer)
{
	assert(apEventBuffer != nullptr);
	return eventBuffers.Add(apEventBuffer);
}

openpal::Indexable<Binary> Database::Binaries() { return staticData.binaries.values; }
openpal::Indexable<Analog> Database::Analogs() { return staticData.analogs.values; }
openpal::Indexable<Counter> Database::Counters() { return staticData.counters.values; }
openpal::Indexable<ControlStatus> Database::ControlStatii() { return staticData.controlStatii; }
openpal::Indexable<SetpointStatus> Database::SetpointStatii() { return staticData.setpointStatii; }

////////////////////////////////////////////////////
// IDataObserver interface
////////////////////////////////////////////////////

void Database::Update(const Binary& value, uint32_t index)
{
	this->UpdateEvent(value, index, staticData.binaries);
}

void Database::Update(const Analog& value, uint32_t index)
{
	this->UpdateEvent(value, index, staticData.analogs);	
}

void Database::Update(const Counter& value, uint32_t index)
{
	this->UpdateEvent(value, index, staticData.counters);
}

void Database::Update(const ControlStatus& value, uint32_t index)
{
	if(staticData.controlStatii.Contains(index)) staticData.controlStatii[index] = value;
}

void Database::Update(const SetpointStatus& value, uint32_t index)
{
	if(staticData.setpointStatii.Contains(index)) staticData.setpointStatii[index] = value;
}

}

