using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace System {
    public class OperationCanceledException : Exception {
        public OperationCanceledException()
            : base("The operation was canceled.") { }

        public OperationCanceledException(String message)
            : base(message) { }

        public OperationCanceledException(String message, Exception innerException)
            : base(message, innerException) { }

        public OperationCanceledException(CancellationToken cancellationToken)
            : this("The operation was canceled.") {
            this.CancellationToken = cancellationToken;
        }

        public OperationCanceledException(String message, CancellationToken cancellationToken)
            : this(message) {
            this.CancellationToken = cancellationToken;
        }

        public OperationCanceledException(String message, Exception innerException, CancellationToken cancellationToken)
            : this(message, innerException) {
            this.CancellationToken = cancellationToken;
        }

        public CancellationToken CancellationToken { get; private set; }
    }
}
