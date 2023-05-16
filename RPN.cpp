#include "RPN.h"

#include <stdexcept>
#include <stack>

struct stack_elm{
    mjs_data* data_ptr;
    variable* variable_ptr;
};

bool RPN::evaluate() {
    std::stack<stack_elm> exec_stack;
    stack_elm left_ptr, right_ptr;


    for (size_t i = 0; i < elements.size(); ++i){
        switch (elements[i].type) {
            case RPN_types::nop:
                continue;
            case RPN_types::jump_false:
                left_ptr = exec_stack.top();
                exec_stack.pop();
                if (not bool(*left_ptr.data_ptr)) i = elements[i].label;
                break;
            case RPN_types::jump_true:
                left_ptr = exec_stack.top();
                exec_stack.pop();
                if (bool(*left_ptr.data_ptr)) i = elements[i].label;
                break;
            case RPN_types::jump:
                i = elements[i].label;
                break;
            case RPN_types::variable_ref:
                exec_stack.push({elements[i].var_ref->data, elements[i].var_ref});
                break;
            case RPN_types::function_ref:
                throw std::logic_error("Not implemented");
                break;
            case RPN_types::constant:
                exec_stack.push({elements[i].const_ref->data});
                break;
            case RPN_types::assign:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr.variable_ptr->data = right_ptr.data_ptr;
                left_ptr.data_ptr = right_ptr.data_ptr;
                break;
            case RPN_types::logical_or:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(*left_ptr.data_ptr || *right_ptr.data_ptr)});
                break;
            case RPN_types::logical_and:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(*left_ptr.data_ptr && *right_ptr.data_ptr)});
                break;
            case RPN_types::eq:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(*left_ptr.data_ptr == *right_ptr.data_ptr)});
                break;
            case RPN_types::neq:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(*left_ptr.data_ptr != *right_ptr.data_ptr)});
                break;
            case RPN_types::identity:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(left_ptr.data_ptr->is_ident(*right_ptr.data_ptr))});
                break;
            case RPN_types::not_identity:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(left_ptr.data_ptr->is_not_ident(*right_ptr.data_ptr))});
                break;
            case RPN_types::ls:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(*left_ptr.data_ptr < *right_ptr.data_ptr)});
                break;
            case RPN_types::le:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(*left_ptr.data_ptr <= *right_ptr.data_ptr)});
                break;
            case RPN_types::gr:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(*left_ptr.data_ptr > *right_ptr.data_ptr)});
                break;
            case RPN_types::ge:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                exec_stack.push({new mjs_bool(*left_ptr.data_ptr >= *right_ptr.data_ptr)});
                break;
            case RPN_types::bin_plus:
                throw std::logic_error("Not implemented");
                break;
            case RPN_types::bin_minus:
                throw std::logic_error("Not implemented");
                break;
            case RPN_types::mul:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                if ((left_ptr.data_ptr->get_type() != mjs_data_types::mjs_number) or
                    (right_ptr.data_ptr->get_type() != mjs_data_types::mjs_number)){
                    throw type_error("Can't mul two non-number objects");
                }
                exec_stack.push({new mjs_number(
                        (*dynamic_cast<mjs_number*>(left_ptr.data_ptr)) * (*dynamic_cast<mjs_number*>(right_ptr.data_ptr))
                        )});
                break;
            case RPN_types::div:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                if ((left_ptr.data_ptr->get_type() != mjs_data_types::mjs_number) or
                    (right_ptr.data_ptr->get_type() != mjs_data_types::mjs_number)){
                    throw type_error("Can't div two non-number objects");
                }
                exec_stack.push({new mjs_number(
                        (*dynamic_cast<mjs_number*>(left_ptr.data_ptr)) / (*dynamic_cast<mjs_number*>(right_ptr.data_ptr))
                )});
                break;
            case RPN_types::mod:
                right_ptr = exec_stack.top();
                exec_stack.pop();
                left_ptr = exec_stack.top();
                exec_stack.pop();
                if ((left_ptr.data_ptr->get_type() != mjs_data_types::mjs_number) or
                    (right_ptr.data_ptr->get_type() != mjs_data_types::mjs_number)){
                    throw type_error("Can't mod two non-number objects");
                }
                exec_stack.push({new mjs_number(
                        (*dynamic_cast<mjs_number*>(left_ptr.data_ptr)) % (*dynamic_cast<mjs_number*>(right_ptr.data_ptr))
                )});
                break;
        }
    }
}