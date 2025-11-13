// *****************************************************************************
//
// Copyright (c) 2025, PFAuto®
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Southwest Research Institute® (SwRI®) nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL SOUTHWEST RESEARCH INSTITUTE BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *****************************************************************************

#include <sstream>

#include <novatel_gps_driver/parsers/gtimu.h>

#include <boost/lexical_cast.hpp>

const std::string novatel_gps_driver::GtimuParser::MESSAGE_NAME = "GTIMU";

uint32_t novatel_gps_driver::GtimuParser::GetMessageId() const
{
  return 0;
}

const std::string novatel_gps_driver::GtimuParser::GetMessageName() const
{
  return MESSAGE_NAME;
}

novatel_gps_driver::GtimuParser::MessageType novatel_gps_driver::GtimuParser::ParseAscii(const novatel_gps_driver::NmeaSentence& sentence) noexcept(false)
{
  // Check the length first -- should be 15 elements long
  const size_t MAX_LEN = 10;
  const size_t MIN_LEN = 9;
  if (sentence.body.size() > MAX_LEN || sentence.body.size() < MIN_LEN)
  {
    std::stringstream error;
    error << "Expected GTIMU length " << MIN_LEN << "  <= length <= "
          << MAX_LEN << ", actual length = " << sentence.body.size();
    throw ParseException(error.str());
  }

  auto msg = std::make_unique<novatel_gps_msgs::msg::Gtimu>();

  msg->message_id = sentence.body[0];

  if (sentence.body[1].empty() || sentence.body[1] == "0")
  {
    msg->gpsweek = 0;
  }
  else
  {
    try
    {
      msg->gpsweek = boost::lexical_cast<int32_t>(sentence.body[1]);
    }
    catch (boost::bad_lexical_cast& e)
    {
      throw ParseException("Error parsing week number in GTIMU");
    }
  }
  if (sentence.body[2].empty() || sentence.body[2] == "0")
  {
    msg->gpstime = 0;
  }
  else
  {
    try
    {
      msg->gpstime = boost::lexical_cast<double>(sentence.body[1]);
    }
    catch (boost::bad_lexical_cast& e)
    {
      throw ParseException("Error parsing week ms in GTIMU");
    }
  }
  bool valid = true;

  valid = valid && ParseDouble(sentence.body[3], msg->gx);
  valid = valid && ParseDouble(sentence.body[4], msg->gy);
  valid = valid && ParseDouble(sentence.body[5], msg->gz);

  valid = valid && ParseDouble(sentence.body[6], msg->ax);
  valid = valid && ParseDouble(sentence.body[7], msg->ay);
  valid = valid && ParseDouble(sentence.body[8], msg->az);

  valid = valid && ParseFloat(sentence.body[9], msg->tpr);

  if (!valid)
  {
    was_last_imu_valid_ = false;
    throw ParseException("GTIMU log was invalid.");
  }
  // If we got this far, we successfully parsed the message and will consider
  // it valid
  was_last_imu_valid_ = true;

  return msg;
}

bool novatel_gps_driver::GtimuParser::WasLastImuValid() const
{
  return was_last_imu_valid_;
}
