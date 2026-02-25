namespace System.Reflection {
    public struct ParameterModifier {
        private bool[] byRef;

        public ParameterModifier(int parameterCount) {
            byRef = new bool[parameterCount];
        }

        public bool this[int index] {
            get {
                return byRef[index];
            }
            set {
                byRef[index] = value;
            }
        }
    }
}
