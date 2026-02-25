// Copyright (c) 2012 DotNetAnywhere
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#if !LOCALTEST

using System.Runtime.CompilerServices;
using System.Reflection;
using System.Collections.Generic;
using System.Globalization;

namespace System {
#pragma warning disable 0660, 0661
    public abstract class Type : MemberInfo {

        public override MemberTypes MemberType => MemberTypes.TypeInfo;

        private static IDictionary<string, Type> typesByNameCache = new Dictionary<string, Type>();

        public static readonly Type[] EmptyTypes = new Type[0];

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static Type GetTypeFromHandle(RuntimeTypeHandle handle);

        extern public TypeAttributes Attributes { [MethodImpl(MethodImplOptions.InternalCall)] get; }

        public abstract string AssemblyQualifiedName { get; }

        public abstract Type BaseType { get; }

        public abstract bool IsEnum { get; }

        public abstract string Namespace { get; }

        public abstract string FullName { get; }

        public abstract bool IsGenericType { get; }

        public abstract Type GetGenericTypeDefinition();

        public abstract Type[] GetGenericArguments();

        public abstract Type GetElementType();

        public virtual bool IsArray => GetElementType() != null;

        public virtual bool IsByRef => false;

        public virtual bool IsPointer => false;

        extern public bool IsValueType { [MethodImpl(MethodImplOptions.InternalCall)] get; }

        public bool IsAnsiClass => (Attributes & TypeAttributes.StringFormatMask) == TypeAttributes.AnsiClass;
        public bool IsUnicodeClass => (Attributes & TypeAttributes.StringFormatMask) == TypeAttributes.UnicodeClass;
        public bool IsAutoClass => (Attributes & TypeAttributes.StringFormatMask) == TypeAttributes.AutoClass;
        public bool IsNotPublic => (Attributes & TypeAttributes.VisibilityMask) == TypeAttributes.NotPublic;
        public bool IsPublic => (Attributes & TypeAttributes.VisibilityMask) == TypeAttributes.Public;
        public bool IsNestedPublic => (Attributes & TypeAttributes.VisibilityMask) == TypeAttributes.NestedPublic;
        public bool IsNestedPrivate => (Attributes & TypeAttributes.VisibilityMask) == TypeAttributes.NestedPrivate;
        public bool IsNestedFamily => (Attributes & TypeAttributes.VisibilityMask) == TypeAttributes.NestedFamily;
        public bool IsNestedAssembly => (Attributes & TypeAttributes.VisibilityMask) == TypeAttributes.NestedAssembly;
        public bool IsNestedFamANDAssem => (Attributes & TypeAttributes.VisibilityMask) == TypeAttributes.NestedFamANDAssem;
        public bool IsNestedFamORAssem => (Attributes & TypeAttributes.VisibilityMask) == TypeAttributes.NestedFamORAssem;
        public bool IsAutoLayout => (Attributes & TypeAttributes.LayoutMask) == TypeAttributes.AutoLayout;
        public bool IsLayoutSequential => (Attributes & TypeAttributes.LayoutMask) == TypeAttributes.SequentialLayout;
        public bool IsExplicitLayout => (Attributes & TypeAttributes.LayoutMask) == TypeAttributes.ExplicitLayout;
        public bool IsClass => (Attributes & TypeAttributes.ClassSemanticsMask) == TypeAttributes.Class && !IsValueType;
        public bool IsInterface => (Attributes & TypeAttributes.ClassSemanticsMask) == TypeAttributes.Interface;
        public bool IsAbstract => (Attributes & TypeAttributes.Abstract) != 0;
        public bool IsSealed => (Attributes & TypeAttributes.Sealed) != 0;
        public bool IsSpecialName => (Attributes & TypeAttributes.SpecialName) != 0;
        public bool IsImport => (Attributes & TypeAttributes.Import) != 0;
        public virtual bool IsSerializable => (Attributes & TypeAttributes.Serializable) != 0;

        public override string ToString() {
            return this.FullName;
        }

        public virtual bool Equals (Type o) {
            return Object.Equals(this, o);
        }

        public virtual Type[] GenericTypeArguments {
            get {
                if (IsGenericType && !IsGenericTypeDefinition) {
                    return GetGenericArguments();
                } else {
                    return Type.EmptyTypes;
                }
            }
        }

        public virtual bool IsGenericTypeDefinition {
            get { return false; }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public virtual bool IsAssignableFrom(Type c);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public virtual bool IsSubclassOf(Type c);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public virtual Type MakeGenericType(params Type[] typeArguments);

        public static Type GetType(string typeName) {
            lock (typesByNameCache) {
                Type cachedResult;
                if (typesByNameCache.TryGetValue(typeName, out cachedResult)) {
                    return cachedResult;
                }
            }

            string assemblyName;
            string namespaceQualifiedTypeName;

            if (typeName.IndexOf(',') > 0) {
                // Assembly is specified
                var parts = typeName.Split(',');
                assemblyName = parts[1].Trim();
                namespaceQualifiedTypeName = parts[0];
            } else {
                // No assembly specified
                assemblyName = null;
                namespaceQualifiedTypeName = typeName;
            }

            var namespaceSplitPoint = namespaceQualifiedTypeName.LastIndexOf('.');
            var namespaceName = namespaceQualifiedTypeName.Substring(0, namespaceSplitPoint).Trim();
            var className = namespaceQualifiedTypeName.Substring(namespaceSplitPoint + 1).Trim();
            var result = GetType(assemblyName, namespaceName, className);

            if (result != null) {
                lock (typesByNameCache) {
                    typesByNameCache[typeName] = result;
                }
            }

            return result;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public Type[] GetNestedTypes();

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public Type GetNestedType(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public Type[] GetInterfaces();

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public MethodInfo[] GetMethods();

        public virtual MethodInfo[] GetMethods(BindingFlags bindingAttr) {
            return GetMethods();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public MethodInfo GetMethod(string name);

        public virtual MethodInfo GetMethod(string name, BindingFlags bindingAttr) {
            return GetMethod(name);
        }

        public virtual MethodInfo GetMethod(string name, Type[] types) {
            return GetMethod(name);
        }

        public virtual MethodInfo GetMethod(string name, BindingFlags bindingAttr, Binder binder, Type[] types, ParameterModifier[] modifiers) {
            return GetMethod(name, bindingAttr);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public PropertyInfo[] GetProperties();

        public virtual PropertyInfo[] GetProperties(BindingFlags bindingAttr) {
            return GetProperties();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public PropertyInfo GetProperty(string name);

        public virtual PropertyInfo GetProperty(string name, BindingFlags bindingAttr) {
            return GetProperty(name);
        }

        public virtual PropertyInfo GetProperty(string name, Type returnType, Type[] types) {
            return GetProperty(name);
        }

        public virtual PropertyInfo GetProperty(string name, BindingFlags bindingAttr, Binder binder, Type returnType, Type[] types, ParameterModifier[] modifiers) {
            return GetProperty(name, bindingAttr);
        }

        public virtual FieldInfo[] GetFields() {
            return new FieldInfo[0];
        }

        public virtual FieldInfo[] GetFields(BindingFlags bindingAttr) {
            return GetFields();
        }

        public virtual FieldInfo GetField(string name) {
            return null;
        }

        public virtual FieldInfo GetField(string name, BindingFlags bindingAttr) {
            return GetField(name);
        }

        public virtual ConstructorInfo[] GetConstructors() {
            return new ConstructorInfo[0];
        }

        public virtual ConstructorInfo[] GetConstructors(BindingFlags bindingAttr) {
            return GetConstructors();
        }

        public virtual ConstructorInfo GetConstructor(Type[] types) {
            return null;
        }

        public virtual ConstructorInfo GetConstructor(BindingFlags bindingAttr, Binder binder, Type[] types, ParameterModifier[] modifiers) {
            return GetConstructor(types);
        }

        public virtual object InvokeMember(string name, BindingFlags invokeAttr, Binder binder, object target, object[] args) {
            return InvokeMember(name, invokeAttr, binder, target, args, CultureInfo.InvariantCulture);
        }

        public virtual object InvokeMember(string name, BindingFlags invokeAttr, Binder binder, object target, object[] args, CultureInfo culture) {
            if ((invokeAttr & BindingFlags.GetProperty) != 0) {
                PropertyInfo p = GetProperty(name);
                return p != null ? p.GetValue(target, args) : null;
            }

            if ((invokeAttr & BindingFlags.SetProperty) != 0) {
                PropertyInfo p = GetProperty(name);
                if (p == null) {
                    return null;
                }

                if (args == null || args.Length == 0) {
                    p.SetValue(target, null, null);
                    return null;
                }

                object value = args[args.Length - 1];
                if (args.Length == 1) {
                    p.SetValue(target, value, null);
                } else {
                    object[] index = new object[args.Length - 1];
                    Array.Copy(args, 0, index, 0, index.Length);
                    p.SetValue(target, value, index);
                }
                return null;
            }

            MethodInfo method = GetMethod(name);
            return method != null ? method.Invoke(target, args) : null;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void EnsureAssemblyLoaded(string assemblyName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern private static Type GetType(string assemblyName, string namespaceName, string className);

        public static bool operator ==(Type t1, Type t2) {
            return t1?.FullName.Equals(t2?.FullName) == true;
        }

        public static bool operator !=(Type t1, Type t2) {
            return t1?.FullName.Equals(t2?.FullName) == false;
        }
    }
#pragma warning restore 0660, 0661
}

#endif
