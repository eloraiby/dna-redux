namespace System.Runtime.ExceptionServices {
    public sealed class ExceptionDispatchInfo {
        private Exception sourceException;

        private ExceptionDispatchInfo(Exception sourceException) {
            this.sourceException = sourceException;
        }

        public Exception SourceException {
            get {
                return sourceException;
            }
        }

        public static ExceptionDispatchInfo Capture(Exception source) {
            if (source == null) {
                throw new ArgumentNullException("source");
            }
            return new ExceptionDispatchInfo(source);
        }

        public void Throw() {
            throw sourceException;
        }

        public static void Throw(Exception source) {
            if (source == null) {
                throw new ArgumentNullException("source");
            }
            throw source;
        }
    }
}
