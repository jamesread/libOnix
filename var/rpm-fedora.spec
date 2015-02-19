Name:		libOnix
Version:	1.0.0
Release:	1%{?dist}
Summary:	A 2d text graphics library

Group:		System Environment/Libraries
License:	GPLv2
URL:		http://github.com/jamesread/libOnix
Source0:	libOnix-%{version}-src.zip

BuildRequires:	cmake

%description
A 2d text graphics library.

%prep
%setup -q


%build
cmake .
make


%install
mkdir -p %{buildroot}%{_libdir}
cp bin/libonix.so %{buildroot}%{_libdir}/libonix.so

mkdir -p %{buildroot}/usr/share/doc/libonix/
cp README.md %{buildroot}/usr/share/doc/libonix/

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%doc /usr/share/doc/libonix/README.md
%{_libdir}/libonix.so


%changelog
* Thu Feb 19 2015 James Read <contact@jwread.com> 1.0.0-1
	Version 1.0.0.
