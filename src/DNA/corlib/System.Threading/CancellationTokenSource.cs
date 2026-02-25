#if !LOCALTEST

using System;

namespace System.Threading {

    public class CancellationTokenSource : IDisposable {
        private bool isCancellationRequested;
        private CancellationToken token;

        public CancellationTokenSource() {
            this.token = new CancellationToken(this);
        }

        public bool IsCancellationRequested {
            get {
                return this.isCancellationRequested;
            }
        }

        public CancellationToken Token {
            get {
                return this.token;
            }
        }

        public void Cancel() {
            this.isCancellationRequested = true;
        }

        public void Dispose() {
        }

        public static CancellationTokenSource CreateLinkedTokenSource(params CancellationToken[] tokens) {
            CancellationTokenSource source = new CancellationTokenSource();
            if (tokens != null) {
                for (int i = 0; i < tokens.Length; i++) {
                    if (tokens[i].IsCancellationRequested) {
                        source.Cancel();
                        break;
                    }
                }
            }
            return source;
        }
    }
}

#endif
