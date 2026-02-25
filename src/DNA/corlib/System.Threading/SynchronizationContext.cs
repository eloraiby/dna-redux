namespace System.Threading {
    public class SynchronizationContext {
        private static SynchronizationContext currentContext;

        public static SynchronizationContext Current {
            get {
                return currentContext;
            }
        }

        public static void SetSynchronizationContext(SynchronizationContext syncContext) {
            currentContext = syncContext;
        }

        public virtual void OperationStarted() {
        }

        public virtual void OperationCompleted() {
        }

        public virtual void Send(SendOrPostCallback d, object state) {
            if (d == null) {
                throw new ArgumentNullException("d");
            }
            d(state);
        }

        public virtual void Post(SendOrPostCallback d, object state) {
            if (d == null) {
                throw new ArgumentNullException("d");
            }
            d(state);
        }

        public virtual SynchronizationContext CreateCopy() {
            return new SynchronizationContext();
        }
    }
}
