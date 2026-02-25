using System.Collections;
using System.Collections.Generic;

namespace System.Collections.Concurrent {
    public class ConcurrentDictionary<TKey, TValue> : IEnumerable<KeyValuePair<TKey, TValue>> {
        private readonly object gate = new object();
        private readonly Dictionary<TKey, TValue> dictionary;

        public ConcurrentDictionary()
            : this((IEqualityComparer<TKey>)null) {
        }

        public ConcurrentDictionary(IEqualityComparer<TKey> comparer) {
            dictionary = comparer == null
                ? new Dictionary<TKey, TValue>()
                : new Dictionary<TKey, TValue>(comparer);
        }

        public int Count {
            get {
                lock (gate) {
                    return dictionary.Count;
                }
            }
        }

        public TValue this[TKey key] {
            get {
                lock (gate) {
                    return dictionary[key];
                }
            }
            set {
                lock (gate) {
                    dictionary[key] = value;
                }
            }
        }

        public void Clear() {
            lock (gate) {
                dictionary.Clear();
            }
        }

        public bool ContainsKey(TKey key) {
            lock (gate) {
                return dictionary.ContainsKey(key);
            }
        }

        public bool TryGetValue(TKey key, out TValue value) {
            lock (gate) {
                return dictionary.TryGetValue(key, out value);
            }
        }

        public bool TryAdd(TKey key, TValue value) {
            lock (gate) {
                if (dictionary.ContainsKey(key)) {
                    return false;
                }
                dictionary.Add(key, value);
                return true;
            }
        }

        public bool TryRemove(TKey key, out TValue value) {
            lock (gate) {
                if (dictionary.TryGetValue(key, out value)) {
                    dictionary.Remove(key);
                    return true;
                }
                return false;
            }
        }

        public TValue GetOrAdd(TKey key, TValue value) {
            lock (gate) {
                TValue existingValue;
                if (dictionary.TryGetValue(key, out existingValue)) {
                    return existingValue;
                }
                dictionary.Add(key, value);
                return value;
            }
        }

        public TValue GetOrAdd(TKey key, Func<TKey, TValue> valueFactory) {
            if (valueFactory == null) {
                throw new ArgumentNullException("valueFactory");
            }

            lock (gate) {
                TValue value;
                if (dictionary.TryGetValue(key, out value)) {
                    return value;
                }
                value = valueFactory(key);
                dictionary.Add(key, value);
                return value;
            }
        }

        public TValue AddOrUpdate(TKey key, Func<TKey, TValue> addValueFactory, Func<TKey, TValue, TValue> updateValueFactory) {
            if (addValueFactory == null) {
                throw new ArgumentNullException("addValueFactory");
            }
            if (updateValueFactory == null) {
                throw new ArgumentNullException("updateValueFactory");
            }

            lock (gate) {
                TValue existingValue;
                if (dictionary.TryGetValue(key, out existingValue)) {
                    TValue updated = updateValueFactory(key, existingValue);
                    dictionary[key] = updated;
                    return updated;
                }

                TValue added = addValueFactory(key);
                dictionary.Add(key, added);
                return added;
            }
        }

        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator() {
            lock (gate) {
                return new List<KeyValuePair<TKey, TValue>>(dictionary).GetEnumerator();
            }
        }

        IEnumerator IEnumerable.GetEnumerator() {
            return GetEnumerator();
        }
    }
}
