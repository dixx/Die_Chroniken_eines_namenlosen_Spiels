namespace leviathan {
    namespace input {
        void EventToActionConverter::clear() {
            _actionsForInput.clear();
        }

        void EventToActionConverter::addMapping(const uint32_t inputId, const uint32_t actionId) {
            _actionsForInput[inputId].push_back(actionId);
            _actionsForInput[inputId].unique();
        }
    }
}
