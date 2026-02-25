#if !LOCALTEST

using System.Globalization;
using System.Reflection;

namespace System.Resources {

    // Minimal resource-manager implementation for libraries that expect this BCL type.
    // This runtime does not load satellite resources, so this returns simple fallbacks.
    public class ResourceManager {

        public ResourceManager(string baseName, Assembly assembly) {
        }

        public ResourceManager(Type resourceSource) {
        }

        protected ResourceManager() {
        }

        public virtual string GetString(string name) {
            return name;
        }

        public virtual string GetString(string name, CultureInfo culture) {
            return name;
        }

        public virtual object GetObject(string name) {
            return null;
        }

        public virtual object GetObject(string name, CultureInfo culture) {
            return null;
        }
    }

    public class MissingManifestResourceException : Exception {
        public MissingManifestResourceException() {
        }

        public MissingManifestResourceException(string message)
            : base(message) {
        }

        public MissingManifestResourceException(string message, Exception innerException)
            : base(message, innerException) {
        }
    }
}

#endif
