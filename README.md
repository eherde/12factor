# 12factor
An exploration of the [12 factor app](http://12factor.net) methodology

## I. Codebase
*One codebase tracked in revision control, many deploys*

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec nec felis a nisi volutpat vehicula non eu nibh. Aenean varius feugiat ex sed congue. Maecenas lobortis eros vitae quam luctus euismod. Etiam sit amet scelerisque est. Nulla convallis dui a tortor efficitur, non aliquam lacus fringilla. Quisque vitae tristique libero, ut hendrerit nisl. Fusce risus lacus, egestas vel ultrices a, sodales quis ex. Cras vestibulum varius lacus in mattis. Etiam interdum massa sapien. In id faucibus dui. Vivamus maximus rutrum nunc, mollis scelerisque eros aliquet at.

## II. Dependencies
*Explicitly declare and isolate dependencies*

- [ ] To enforce *dependency isolation*, external libraries must be statically linked to the programs of this application.
- [ ] To enforce *dependency declaration*, external libraries must be declared in a *dependency declaration* manifest.

The inclusion of the external dependency hiredis causes a few complications. Although 12 factor suggests that libraries should be statically linked, the following error occurs when linking to libhiredis.a:
> warning: Using 'getaddrinfo' in statically linked applications requires at runtime the shared libraries from the glibc version used for linking

Some investigation indicates that libnss, which is used by glibc, cannot be statically linked. The reason behind this is unclear. The article [Static Linking Considered Harmful](http://www.akkadia.org/drepper/no_static_linking.html) has some strong opinions on the matter.

## III. Config
*Store config in the environment*

This approach has some immediate drawbacks. Environment variables lack the depth and complexity that other configuration methods such as yaml and json provide.
The 12 factor documentation does not provide guidance on how to correctly implement this approach. It states:
> In a twelve-factor app, env vars are granular controls, each fully orthogonal to other env vars.

The authenticity of this assertion should be explored.

## IV. Backing Services
*Treat backing services as attached resources*

The redis backing service uses the below environment variables:
```
_12RDIP=127.0.0.1 # redis ip address
_12RDPORT=6379    # redis port
```

## V. Build, release, run
*Strictly separate build and run stages*

The app has three separate stages:
* Build:   ```make```
* Release: ```DESTDIR=<path> PREFIX=<path> make install```
* Run:     ```$DESTDIR$PREFIX/bin/svc1```

## VI. Processes
*Execute the app as one or more stateless processes*

Sed rhoncus ornare molestie. Nulla consectetur elit eget felis rutrum ullamcorper. Pellentesque eget lorem sagittis, eleifend dui at, tincidunt urna. Pellentesque leo ipsum, ornare eu rutrum sed, auctor sit amet quam. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Maecenas vestibulum massa ipsum, eu pellentesque orci fermentum quis. Sed commodo fermentum ornare.

## VII. Port binding
*Export services via port binding*

Duis fringilla consequat egestas. Phasellus imperdiet porta erat, nec malesuada ipsum. Suspendisse feugiat, tellus ut faucibus lacinia, quam odio fringilla lacus, sed convallis elit urna ut mauris. Maecenas porttitor commodo magna, ut eleifend nunc sollicitudin in. Nunc maximus mi sit amet erat dignissim, nec placerat leo tempor. Phasellus varius dui nisi, auctor hendrerit diam consectetur id. Phasellus molestie lobortis leo eget porttitor. Nullam rhoncus sagittis tortor, nec tincidunt neque placerat in. Fusce et semper nunc. Nam quis semper metus. Ut tincidunt erat ullamcorper gravida vehicula.

## VIII. Concurrency
*Scale out via the process model*

Integer nec eros vulputate, pharetra mi et, posuere nulla. Mauris erat risus, faucibus non euismod sit amet, consectetur quis nisi. Suspendisse tempus, lorem sit amet commodo mattis, nibh nisi scelerisque est, in egestas velit ante at velit. Integer neque mauris, accumsan eu metus eu, luctus sagittis purus. Aenean pulvinar mattis urna sodales vehicula. Quisque ut arcu vel diam congue dignissim. Vestibulum tempor, risus euismod tristique cursus, arcu odio rhoncus elit, eget semper nisi purus euismod est. Suspendisse suscipit varius dui, sit amet aliquam velit sollicitudin eu. Integer non arcu rhoncus, congue elit sed, gravida justo. Cras vestibulum, justo vitae placerat facilisis, neque quam gravida justo, eget pulvinar tortor mauris nec nisi. Donec suscipit arcu vel sem aliquam lobortis. Nullam id odio et ex feugiat placerat vel at quam. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin accumsan laoreet auctor.

## IX. Disposability
*Maximize robustness with fast startup and graceful shutdown*

Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Suspendisse non turpis ut eros dignissim elementum ac id quam. Vivamus finibus eget augue in lacinia. Curabitur iaculis, justo in auctor dictum, ante sapien egestas libero, a cursus velit ipsum non lorem. Nulla nec odio eget est volutpat rutrum. In in massa neque. Integer condimentum quis elit id ultrices. Fusce gravida, nulla egestas imperdiet rutrum, mi tellus ornare nunc, quis finibus purus orci at odio. Proin dictum porta erat, in congue risus scelerisque nec. Nunc tincidunt at sapien vitae accumsan. Praesent mollis nunc a dictum cursus. Suspendisse accumsan non lorem nec cursus.

## X. Dev/prod parity
*Keep development, staging, and production as similar as possible*

Proin velit elit, mattis non eros non, vestibulum sagittis nisl. Ut quis magna quam. Nullam tellus erat, fringilla at sem non, efficitur eleifend diam. Donec ac libero ut velit rutrum suscipit. Vestibulum vulputate sollicitudin imperdiet. Pellentesque consectetur arcu id dui semper efficitur et vel nisi. Etiam euismod nibh non ante malesuada ullamcorper. Aenean semper pulvinar enim, eget pretium urna placerat id. Interdum et malesuada fames ac ante ipsum primis in faucibus. Integer nec purus a diam dapibus auctor id et eros. Duis elementum a est luctus accumsan. Sed fringilla sit amet nisi blandit sodales. Praesent diam magna, rutrum quis rutrum et, luctus id tortor.

## XI. Logs
*Treat logs as event streams*

We use the setvbuf(3) function to change stdout to unbuffered, then start logging some information. This output can now be redirected to a file or external log handling service. One interesting problem here is how log levels interact with 12 factor. We can either set log levels within each service, or we can log everything  and let the consumer of the logs filter down to the level they want. Both options have their merits and should be evaluated.


## XII. Admin processes
*Run admin/management tasks as one-off processes*

Nullam vitae pretium ante, et venenatis elit. Nulla ac facilisis quam. Nulla sit amet sem vitae elit sollicitudin gravida. Proin maximus ornare sodales. Praesent vitae accumsan urna. Sed mi lacus, molestie nec tempor quis, aliquet vel eros. Morbi posuere nunc lorem, sed vulputate sapien lobortis non. Etiam pretium ante non arcu varius placerat. Cras vitae ex neque. Aenean sagittis, mi ac blandit aliquet, est elit vulputate justo, sit amet varius odio tortor eu augue. Etiam purus risus, dictum imperdiet lacinia finibus, tincidunt eget dolor. Duis ex mauris, maximus ac sapien ut, faucibus ullamcorper tellus. Aenean magna sapien, aliquet et tortor vitae, ullamcorper hendrerit dui. Sed scelerisque mattis tempus. Sed risus diam, convallis eu aliquam in, volutpat eget lorem.
