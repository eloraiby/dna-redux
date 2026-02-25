#if !LOCALTEST

using System;

namespace System.Threading {

    public struct CancellationTokenRegistration : IDisposable, IEquatable<CancellationTokenRegistration> {

        public void Dispose() {
        }

        public bool Equals(CancellationTokenRegistration other) {
            return true;
        }

        public override bool Equals(object obj) {
            return obj is CancellationTokenRegistration;
        }

        public override int GetHashCode() {
            return 0;
        }

        public static bool operator ==(CancellationTokenRegistration left, CancellationTokenRegistration right) {
            return true;
        }

        public static bool operator !=(CancellationTokenRegistration left, CancellationTokenRegistration right) {
            return false;
        }
    }
}

#endif
