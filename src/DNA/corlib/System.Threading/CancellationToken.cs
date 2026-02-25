#if !LOCALTEST

using System;

namespace System.Threading {

    public struct CancellationToken : IEquatable<CancellationToken> {
        private CancellationTokenSource source;

        internal CancellationToken(CancellationTokenSource source) {
            this.source = source;
        }

        public static CancellationToken None {
            get {
                return default(CancellationToken);
            }
        }

        public bool CanBeCanceled {
            get {
                return this.source != null;
            }
        }

        public bool IsCancellationRequested {
            get {
                return this.source != null && this.source.IsCancellationRequested;
            }
        }

        public WaitHandle WaitHandle {
            get {
                return null;
            }
        }

        public CancellationTokenRegistration Register(Action callback) {
            if (callback != null && this.IsCancellationRequested) {
                callback();
            }
            return default(CancellationTokenRegistration);
        }

        public CancellationTokenRegistration Register(Action<object> callback, object state) {
            if (callback != null && this.IsCancellationRequested) {
                callback(state);
            }
            return default(CancellationTokenRegistration);
        }

        public void ThrowIfCancellationRequested() {
            if (this.IsCancellationRequested) {
                throw new OperationCanceledException(this);
            }
        }

        public bool Equals(CancellationToken other) {
            return this.source == other.source;
        }

        public override bool Equals(object obj) {
            return obj is CancellationToken && this.Equals((CancellationToken)obj);
        }

        public override int GetHashCode() {
            return this.source == null ? 0 : this.source.GetHashCode();
        }

        public static bool operator ==(CancellationToken left, CancellationToken right) {
            return left.Equals(right);
        }

        public static bool operator !=(CancellationToken left, CancellationToken right) {
            return !left.Equals(right);
        }
    }
}

#endif
