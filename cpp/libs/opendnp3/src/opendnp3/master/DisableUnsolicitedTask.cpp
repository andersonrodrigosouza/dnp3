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

#include "DisableUnsolicitedTask.h"

#include "opendnp3/app/APDUBuilders.h"

#include "MasterTasks.h"

using namespace openpal;

namespace opendnp3
{

DisableUnsolicitedTask::DisableUnsolicitedTask(const MasterParams& params, openpal::Logger* pLogger_) : 
	NullResponseTask(pLogger_),
	pParams(&params),
	expiration(0)
{

}

void DisableUnsolicitedTask::BuildRequest(APDURequest& request, uint8_t seq)
{
	build::DisableUnsolicited(request, seq);
}

openpal::MonotonicTimestamp DisableUnsolicitedTask::ExpirationTime() const
{
	return pParams->disableUnsolOnStartup ? expiration : MonotonicTimestamp::Max();
}

void DisableUnsolicitedTask::OnSuccess(const openpal::MonotonicTimestamp&)
{
	expiration = MonotonicTimestamp::Max();
}

void DisableUnsolicitedTask::OnBadControlOctet(const openpal::MonotonicTimestamp& now)
{
	expiration = MonotonicTimestamp::Max();
}

void DisableUnsolicitedTask::OnRejectedIIN(const openpal::MonotonicTimestamp& now)
{
	expiration = MonotonicTimestamp::Max();
}

void DisableUnsolicitedTask::OnResponseTimeout(const openpal::MonotonicTimestamp& now)
{
	expiration = now.Add(pParams->taskRetryPeriod);
}

void DisableUnsolicitedTask::OnLowerLayerClose(const openpal::MonotonicTimestamp&)
{
	expiration = 0;
}

void DisableUnsolicitedTask::Demand()
{
	if (expiration.IsMax())
	{
		expiration = 0;
	}
}

} //end ns

