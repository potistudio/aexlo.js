<div align=center>
	<img src="https://count.getloli.com/@aexlo.js" alt="aexlo.js" />
</div>

# aexlo.js

Load and Host "After Effects Effect Plugin (.aex)"

# Announcement

The development of aexlo.js has stopped and **we have moved to development using Rust called [aexlo-rs](https://github.com/potistudio/aexlo-rs) instead.**  
Node.js support has been abandoned in terms of performance due to the overhead of data conversion between JS and C++.  
Therefore, we have decided to continue developing the product in the future for limited use as an embedded library for Rust. (Because the compiled library can be applied to any language)

## Why

"Adobe After Effects (AE)" is currently the most widely used Video Editor in the world.  
There are many plugins for AE available on the internet.  
However, almost all of them are made to work **only** with AE.  
(Even if it's a very good effect)

So I wondered if I could make these work on another platform.  
What I ended up doing was **creating a emulator for the AE Plugin SDK.**

(These may run into some kind of copyright issue.)
