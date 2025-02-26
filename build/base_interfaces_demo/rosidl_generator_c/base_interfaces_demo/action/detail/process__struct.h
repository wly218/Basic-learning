// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interfaces_demo:action/Process.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES_DEMO__ACTION__DETAIL__PROCESS__STRUCT_H_
#define BASE_INTERFACES_DEMO__ACTION__DETAIL__PROCESS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in action/Process in the package base_interfaces_demo.
typedef struct base_interfaces_demo__action__Process_Goal
{
  int64_t num;
} base_interfaces_demo__action__Process_Goal;

// Struct for a sequence of base_interfaces_demo__action__Process_Goal.
typedef struct base_interfaces_demo__action__Process_Goal__Sequence
{
  base_interfaces_demo__action__Process_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__action__Process_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/Process in the package base_interfaces_demo.
typedef struct base_interfaces_demo__action__Process_Result
{
  int64_t sum;
} base_interfaces_demo__action__Process_Result;

// Struct for a sequence of base_interfaces_demo__action__Process_Result.
typedef struct base_interfaces_demo__action__Process_Result__Sequence
{
  base_interfaces_demo__action__Process_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__action__Process_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/Process in the package base_interfaces_demo.
typedef struct base_interfaces_demo__action__Process_Feedback
{
  double process;
} base_interfaces_demo__action__Process_Feedback;

// Struct for a sequence of base_interfaces_demo__action__Process_Feedback.
typedef struct base_interfaces_demo__action__Process_Feedback__Sequence
{
  base_interfaces_demo__action__Process_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__action__Process_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "base_interfaces_demo/action/detail/process__struct.h"

/// Struct defined in action/Process in the package base_interfaces_demo.
typedef struct base_interfaces_demo__action__Process_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  base_interfaces_demo__action__Process_Goal goal;
} base_interfaces_demo__action__Process_SendGoal_Request;

// Struct for a sequence of base_interfaces_demo__action__Process_SendGoal_Request.
typedef struct base_interfaces_demo__action__Process_SendGoal_Request__Sequence
{
  base_interfaces_demo__action__Process_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__action__Process_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/Process in the package base_interfaces_demo.
typedef struct base_interfaces_demo__action__Process_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} base_interfaces_demo__action__Process_SendGoal_Response;

// Struct for a sequence of base_interfaces_demo__action__Process_SendGoal_Response.
typedef struct base_interfaces_demo__action__Process_SendGoal_Response__Sequence
{
  base_interfaces_demo__action__Process_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__action__Process_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/Process in the package base_interfaces_demo.
typedef struct base_interfaces_demo__action__Process_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} base_interfaces_demo__action__Process_GetResult_Request;

// Struct for a sequence of base_interfaces_demo__action__Process_GetResult_Request.
typedef struct base_interfaces_demo__action__Process_GetResult_Request__Sequence
{
  base_interfaces_demo__action__Process_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__action__Process_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "base_interfaces_demo/action/detail/process__struct.h"

/// Struct defined in action/Process in the package base_interfaces_demo.
typedef struct base_interfaces_demo__action__Process_GetResult_Response
{
  int8_t status;
  base_interfaces_demo__action__Process_Result result;
} base_interfaces_demo__action__Process_GetResult_Response;

// Struct for a sequence of base_interfaces_demo__action__Process_GetResult_Response.
typedef struct base_interfaces_demo__action__Process_GetResult_Response__Sequence
{
  base_interfaces_demo__action__Process_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__action__Process_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "base_interfaces_demo/action/detail/process__struct.h"

/// Struct defined in action/Process in the package base_interfaces_demo.
typedef struct base_interfaces_demo__action__Process_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  base_interfaces_demo__action__Process_Feedback feedback;
} base_interfaces_demo__action__Process_FeedbackMessage;

// Struct for a sequence of base_interfaces_demo__action__Process_FeedbackMessage.
typedef struct base_interfaces_demo__action__Process_FeedbackMessage__Sequence
{
  base_interfaces_demo__action__Process_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__action__Process_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACES_DEMO__ACTION__DETAIL__PROCESS__STRUCT_H_
